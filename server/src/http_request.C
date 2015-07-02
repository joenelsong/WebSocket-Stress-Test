#include <http_request.h>
#include <string>
#include <iostream>
#include <sstream>
using std::string;

const string& HTTP_Request::getWebSocketKey() const
{
	return webSocketKey;
}
	
void HTTP_Request::setWebSocketKey(const string& key)
{
	webSocketKey = key;
}

/*
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