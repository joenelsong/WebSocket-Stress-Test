#include <tcp_listener.h>
#include <iostream>
#include <exception>

int main( int argc, char *argv[] )
{
    std::cout << "Starting Suede Server" << std::endl;
    try
    {
        TCP_Listener listener;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    std::cout << "Shutting Down Suede Server" << std::endl;
    return 0;
}