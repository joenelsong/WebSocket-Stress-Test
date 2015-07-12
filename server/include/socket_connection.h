#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H
#include <string>
using std::string;

class Socket_Connection
{
private:
    struct sockaddr* cli_addr;
public:
    Socket_Connection( struct sockaddr*);
};

#endif