#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H
#include <string>
using std::string;

class TCP_Listener
{
private:
	void listenForTCPConnections();
	void listenToConnectedSocket(int);
	void listenForWebSocketFrames(int);
	void performHTTPHandshake(int);
public:
    TCP_Listener();
};

#endif