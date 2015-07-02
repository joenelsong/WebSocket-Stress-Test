#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include <string>
using std::string;

class HTTP_Request
{
private:
    string method;
    string resourceRequested;
    string host;
    string upgrade;
    string connection;
    string webSocketKey;
    string webSocketProtocol;
    string webSocketVersion;
    string origin;
public:
    const string& getWebSocketKey() const;
    void setWebSocketKey(const string&);
    static HTTP_Request* buildRequestFromString(const string&); // Factory Method
};

#endif