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
using std::string;


void TCP_Listener::startListening()
{
    int sockfd, newsockfd, portno, clilen;
	char buffer[1028];
	struct sockaddr_in serv_addr, cli_addr;
	int  n;

	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		exit(1);
	}

	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = 80;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("ERROR on binding");
		exit(1);
	}
	printf("Waiting for message from client...\n");
	/* Now start listening for the clients, here process will
	* go in sleep mode and will wait for the incoming connection
	*/

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	/* Accept actual connection from the client */
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *) &clilen);
	if (newsockfd < 0)
	{
		perror("ERROR on accept");
		exit(1);
	}

	/* If connection is established then start communicating */
	bzero(buffer,1028);
	n = read( newsockfd,buffer,1028 );

	if (n < 0)
	{
		perror("ERROR reading from socket");
		exit(1);
	}

	printf("Here is the message: %s\n",buffer);

	HTTP_Request *request = HTTP_Request::buildRequestFromString(*(new string(buffer)));

	printf("Websocket Key:%s\n", request->getWebSocketKey().c_str() );

	HTTP_Response *response = HTTP_Response::buildResponseToRequest(request);
	//string generatedKey = generateWebSocketAcceptVal(request->getWebSocketKey());

	//printf("Generated Websocket Key:%s\n", generatedKey.c_str() );
	string responseString = response->toString();
	n = write(newsockfd,
		responseString.c_str(),
		responseString.size());

	if (n < 0)
	{
		perror("ERROR writing to socket");
		exit(1);
	}

	bzero(buffer,1024);
	n = read( newsockfd,buffer,1028);

	if (n < 0)
	{
		perror("ERROR reading from socket second time");
		exit(1);
	}

	/*printf("Frame Bytes result:");
        for (int i = 0; i < 1024; i++)
        {
            printf(" %02X ", buffer[i]);
        }
        printf("\n");*/

	WebSocket_Frame* frame = WebSocket_Frame::buildFrameFromString(*(new string(buffer)));

	printf("Here is the message 2: %s\n",frame->getStringPayload().c_str());
}

TCP_Listener::TCP_Listener()
{
    FIN = false;
    RSV1 = false;
    RSV2 = false;
    RSV3 = false;
    startListening();
}