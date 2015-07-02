#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H
#include <string>
using std::string;

class TCP_Listener
{
private:
	bool FIN;
	bool RSV1;
	bool RSV2;
	bool RSV3;
	bool opcode;
	bool mask;
	int payloadLen;
	int extendedPayloadLen;
	string webSocketKey;
	unsigned char *webSocketProtocol;
	unsigned char *webSocketVersion;
	unsigned char *origin;
	void startListening();
public:
    TCP_Listener();
};

#endif