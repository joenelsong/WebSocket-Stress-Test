#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <http_response.h>
#include <http_request.h>
#include <stdlib.h>
#include <cstring>
#include <string>
using std::string;

//Sort of based on solution from stack overflow, may need rewrite as it seems to have memory leak in valgrind
static char *base64(const unsigned char *input, int length, char **buffer)
{
    BIO *bmem, *b64;
    BUF_MEM *bptr;
    b64 = BIO_new(BIO_f_base64());//This seems to be the source of some memory leaks that need to be resolved
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    *buffer = new char[bptr->length + 1];
    memcpy(*buffer, bptr->data, bptr->length);
    (*buffer)[bptr->length] = 0;
    BIO_free_all(b64); // This should stop the memory leak
}

static string generateWebSocketAcceptVal(const string& clientKey)
{
	unsigned char hashResult[20];
	char *outBuffer = NULL;
	printf("Client Key:%s\n", clientKey.c_str());
	string localKeyCopy(clientKey.c_str());
	printf("Local Client Key:%s\n", localKeyCopy.c_str());
	string guid("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
	printf("GUID:%s\n", guid.c_str());
	string combined = clientKey + guid;
	printf("Combined Key cat GUID:%s\n", combined.c_str());
	SHA1((const unsigned char*) combined.c_str(), combined.size(), hashResult);
	printf("Hash result:");
    for (int i = 0; i < 20; i++)
    {
        printf("%02X", hashResult[i]);
    }
	printf("\n");
	base64(hashResult, 20, &outBuffer);
    printf("Base64Encoded:%s\n", outBuffer);
	string finalString(outBuffer);
	delete[] outBuffer;
	return finalString;
}

/**
 * This is a factory method that constructs HTTP_Response a 
 * provided HTTP_Request request.
 * @param request pointer to HTTP_Request for which the response is created for
 * @return response A HTTP_Response constructed from the binary buffer contents
 */
HTTP_Response* HTTP_Response::buildResponseToRequest(const HTTP_Request *request)
{
    HTTP_Response *response = new HTTP_Response();
    string clientKey = request->getWebSocketKey();
    string generatedKey = generateWebSocketAcceptVal(clientKey);
	//TODO: don't use setResponseString, build a real HTTP_Response object that can be used for other things
    response->setResponseString("HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: "+ generatedKey +"\r\nSec-WebSocket-Protocol: chat\r\n\r\n");
    return response;
}

//temporary for emulating toString construction
void HTTP_Response::setResponseString(const string& testIn) //temporary
{
	responseString = testIn;
}

/**
 * toString Method generates text http response.
 * @return responseString String that is a text version of the http request, 
 * fully prepared for transmission
 */
const string& HTTP_Response::toString() const
{
	//TODO: make this a proper string construction
    return responseString;
}