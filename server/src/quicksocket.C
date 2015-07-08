#include <tcp_listener.h>
#include <iostream>
#include <exception>

/**
 * Application Main function. Creates and starts TCP_Listener.
 * @param argc number of arguments passed into application
 * @param argv array of character arrays, each character array is a
 * parameter passed into application
 * @return status Application exit status
 */
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