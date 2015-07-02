#ifndef WEBSOCKET_FRAME_H
#define WEBSOCKET_FRAME_H
#include <string>
using std::string;

class WebSocket_Frame
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
public:
    string getStringPayload();
	static WebSocket_Frame* buildFrameFromString(const string&); // Factory Method
};

#endif