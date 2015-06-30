#include <HTTPrequest.h>
#include <string>
using std::string;

string HTTPrequest::GetWebSocketKey()
{
	return webSocketKey;
}
	
void HTTPrequest::SetWebSocketKey(const string &key)
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
HTTPrequest *HTTPrequest::buildRequestFromString(const string &httpString)
{
	HTTPrequest *request = new HTTPrequest();
	return request;
}