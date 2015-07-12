#include <tcp_listener.h>
#include <http_request.h>
#include <http_response.h>
#include <websocket_frame.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>

#include <thread>
#include <iostream>
#include <arpa/inet.h>
using std::string;

void userInputListener(string& userInput, int& sockfd)
{
    while(true){
        string input;
        std::cin >> input;
        if (input == "exit"){
            std::cout << "exit command received" << std::endl;
            userInput = "exit";
            shutdown(sockfd, 2);
            return;
        }else {
            std::cout << "Not a valid command" << std::endl;
        }
    }
}

void TCP_Listener::performHTTPHandshake(int socketfd)
{
    unsigned char buffer[1028];
    bzero(buffer,1028);
	int n = read( socketfd,buffer,1028 );

	if (n < 0){
		perror("ERROR reading from socket");
		exit(1);
	}

	printf("incoming HTTP message:\n%s\n",buffer);

	HTTP_Request *request = HTTP_Request::buildRequestFromBuffer(buffer);

	HTTP_Response *response = HTTP_Response::buildResponseToRequest(request);

	string responseString = response->toString();
	n = write(socketfd, responseString.c_str(), responseString.size());

	printf("HTTP Response:\n%s\n", responseString.c_str() );

	if (n < 0)
	{
		perror("ERROR writing to socket");
		exit(1);
	}

	delete request;
    delete response;
}

void TCP_Listener::listenForWebSocketFrames(int socketfd)
{
    unsigned char buffer[1028];
    bzero(buffer,1024);
    int n = read( socketfd,buffer,1028);

    if (n < 0)
    {
        perror("ERROR reading from socket second time");
        exit(1);
    }

    /*printf("Frame Bytes result:");
        for (int i = 0; i < 1028; i++)
        {
            printf(" %02X ", buffer[i]);
        }
        printf("\n");*/

    bool hasMask = (bool) (buffer[1] & 0x80);
    if(hasMask){
        printf("frame payload uses mask\n");
    }

    int payloadLength = (int) (buffer[1] & 0x7F);
    //int payloadLength = (int) (buffer[1]);
    printf("frame payload uses has byte length of %d\n", payloadLength);

    char payloadText[payloadLength + 1];
    for(int i = 0; i < payloadLength; i++){
        payloadText[i] = buffer[6 + i] ^ buffer[ i % 4 + 2];
    }

  //  WebSocket_Frame* frame = WebSocket_Frame::buildFrameFromBuffer(buffer);

    printf("Here is the WebSocket message:\n%s\n", payloadText);

    unsigned char webSocketResponse[payloadLength + 2];
    webSocketResponse[0] = 0x81;
    webSocketResponse[1] = payloadLength;
    for(int i = 0; i < payloadLength; i++){
        webSocketResponse[i + 2] = payloadText[i];
    }

    n = write(socketfd, webSocketResponse, payloadLength + 2);
    printf("Websocket echo sent.\n");

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }
    //delete frame;
}

void TCP_Listener::listenToConnectedSocket(int socketfd)
{
    performHTTPHandshake(socketfd);
    listenForWebSocketFrames(socketfd);
}

void TCP_Listener::listenForTCPConnections()
{
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    string userInput = "";

    portno = 80;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 80;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }
    std::thread inputListenThread(userInputListener, std::ref(userInput), std::ref(sockfd));
    while(userInput != "exit"){//userInput controlled by inputListenThread
        printf("Waiting for message from client...\n");

        listen(sockfd,5);
        clilen = sizeof(cli_addr);

        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *) &clilen);
        if (newsockfd < 0 && userInput != "exit")
        {
            std::cerr << "ERROR on accept" << std::endl;
            exit(1);
        } else if(userInput == "exit")
        {
        inputListenThread.join();
            std::cout << "Closing Listeners" << std::endl;
            return;
        }
        printf("Connection established to: %s\n", inet_ntoa(cli_addr.sin_addr));
        listenToConnectedSocket(newsockfd);
    }
}

/**
 * Default constructor for TCP_Listener, starts listening
 */
TCP_Listener::TCP_Listener()
{
    listenForTCPConnections();
}