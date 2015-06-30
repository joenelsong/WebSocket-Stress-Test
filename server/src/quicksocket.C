#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <string>
#include <HTTPrequest.h>
using std::string;

/*
char *base64(const unsigned char *input, int length)
{
  BIO *bmem, *b64;
  BUF_MEM *bptr;
  char *buffer;
  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, input, length);
  BIO_flush(b64);
  BIO_get_mem_ptr(b64, &bptr);

  char *buffer = (char *)malloc(bptr->length);
  memcpy(buffer, bptr->data, bptr->length);
  buffer[bptr->length] = 0;

  BIO_free_all(b64);
}*/

/*char * generateWebSocketAcceptVal(char *clientKey){
	const char *guid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
	char *tempBuffer = null;
	char *hashResult[20];
	char *outBuffer = null;
	tempBuffer = malloc(strlen(inBuffer) + strlen(guid) + 1); *//* make space for the new string (should check the return value ...) */
//	strcpy(tempBuffer, inBuffer); /* copy current inBuffer into the new var */
//	strcat(tempBuffer, guid); /* add the gui */
/*	SHA1(tempBuffer, tempBuffer + 1, hashResult);
	base64(hashResult, 20, outBuffer);
	return outBuffer
}*/
/*
string extractStringFromHeader(string header){
	
}
*/
int main( int argc, char *argv[] )
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
	HTTPrequest *request = HTTPrequest::buildRequestFromString(*(new string(buffer)));
	//String header(buffer);
	//char * encodedResponseCode = base64(hash, 1028);
	/* Write a response to the client */
	n = write(newsockfd,
		"HTTP/1.1 101 Switching Protocols\nUpgrade: websocket\nConnection: Upgrade\nSec-WebSocket-Accept: encodedResponseCode\nSec-WebSocket-Protocol: chat"
		,18);

	if (n < 0)
	{
		perror("ERROR writing to socket");
		exit(1);
	}

	return 0;
	}
