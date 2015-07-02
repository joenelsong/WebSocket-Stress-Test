#include <websocket_frame.h>
#include <sstream>
#include <string>
using std::string;

const string& WebSocket_Frame::getStringPayload()
{
    return stringPayload;
}

void WebSocket_Frame::setStringPayload(const string& payload)
{
    stringPayload = payload;
}

WebSocket_Frame::WebSocket_Frame()
{
    FIN = RSV1 = RSV2 = RSV3 = opcode = hasMask = isStringPayload = isBinaryPayload = false;
	payloadLength = extendedPayloadLength = 0;
	payloadMask = NULL;
	string stringPayload = "";
	binaryPayload = NULL;
}

/**
 * This is a factory method that constructs WebSocket_Frame from a buffer
 * It does so according to the Websocket frame specification as outlined
 * in https://tools.ietf.org/html/rfc6455
 *
 *   0                   1                   2                   3
 *    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *   +-+-+-+-+-------+-+-------------+-------------------------------+
 *   |F|R|R|R| opcode|M| Payload len |    Extended payload length    |
 *   |I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
 *   |N|V|V|V|       |S|             |   (if payload len==126/127)   |
 *   | |1|2|3|       |K|             |                               |
 *   +-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
 *   |     Extended payload length continued, if payload len == 127  |
 *   + - - - - - - - - - - - - - - - +-------------------------------+
 *   |                               |Masking-key, if MASK set to 1  |
 *   +-------------------------------+-------------------------------+
 *   | Masking-key (continued)       |          Payload Data         |
 *   +-------------------------------- - - - - - - - - - - - - - - - +
 *   :                     Payload Data continued ...                :
 *   + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
 *   |                     Payload Data continued ...                |
 *   +---------------------------------------------------------------+
 * @param data binary
 */
WebSocket_Frame* WebSocket_Frame::buildFrameFromBuffer(unsigned const char* const data ) {
    // be sure that we dont make unsafe typecast of unsigned into string
    WebSocket_Frame* frame = new WebSocket_Frame();
    frame->setStringPayload("Fake Message");
    // TODO : Setup the frame, parse out fields and unmask the payload data
    return frame;
}