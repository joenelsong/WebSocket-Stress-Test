#include <http_request.h>
#include <string>
#include <iostream>
#include <sstream>
using std::string;

/**
 * Getter for webSocketKey
 * @return webSocketKey String webSocketKey member data
 */
const string& HTTP_Request::getWebSocketKey() const
{
	return webSocketKey;
}

/**
 * Setter for webSocketKey
 * @param key string object that will be set as webSocketKey
 * @return void
 */
void HTTP_Request::setWebSocketKey(const string& key)
{
	webSocketKey = key;
}

/**
 * This is a factory method that constructs HTTP_Request from a buffer
 * @param data A binary buffer that contains the raw HTTP Request
 * data directly from the network
 * @return request A HTTP_Request constructed from the binary buffer contents
 
 * Factory method that constructs HTTPrequest from following string format:
 * GET /chat HTTP/1.1
 * Host: server.example.com
 * Upgrade: websocket
 * Connection: Upgrade
 * Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==
 * Sec-WebSocket-Protocol: chat, superchat
 * Sec-WebSocket-Version: 13
 * Origin: http://example.com
*/
HTTP_Request *HTTP_Request::buildRequestFromBuffer(unsigned const char* const data)
{
    string httpString((char*)data); // May not be a safe typecast since unsigned version may not have null terminator
	HTTP_Request *request = new HTTP_Request();
	std::istringstream stringStream(httpString);
    std::string line;    
    while (std::getline(stringStream, line)) {
		if (line.find("Sec-WebSocket-Key: ") == 0) {
			request->setWebSocketKey(line.substr(19, 24));
			//seems like this always work but may need to change to something like line.substr(19, line.size() - 20)
		}
    }
	return request;
}