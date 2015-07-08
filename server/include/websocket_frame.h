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
	bool hasMask;
	bool isStringPayload;
	bool isBinaryPayload;
	int payloadLength;
	int extendedPayloadLength;
	unsigned char* payloadMask;
	string stringPayload;
	unsigned char* binaryPayload;
public:
    WebSocket_Frame();
    const string& getStringPayload();
    void setStringPayload(const string&);
	static WebSocket_Frame* buildFrameFromBuffer(unsigned const char* const); // Factory Method
};

#endif