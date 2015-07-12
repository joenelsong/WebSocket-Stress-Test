#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H
#include <string>
#include <thread>
#include <vector>
using std::string;

class TCP_Listener
{
private:
    std::vector<std::thread*> connectedThreads;
	void listenForTCPConnections();
	//void listenToConnectedSocket(int);
	//void listenForWebSocketFrames(int);
	//void performHTTPHandshake(int);
public:
    TCP_Listener();
};

#endif