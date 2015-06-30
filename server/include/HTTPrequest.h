#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <string>
using std::string;

class HTTPrequest
{
private:
	unsigned char *method;
	unsigned char *resourceRequested;
	unsigned char *host;
	unsigned char *upgrade;
	unsigned char *connection;
	string webSocketKey;
	unsigned char *webSocketProtocol;
	unsigned char *webSocketVersion;
	unsigned char *origin;
public:
	string GetWebSocketKey();
	void SetWebSocketKey(const string &key);
	static HTTPrequest *buildRequestFromString(const string &); // Factory Method
};

#endif