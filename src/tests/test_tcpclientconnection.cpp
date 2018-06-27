#include "network/TcpConnection.h"
#include "network/TcpConnectionHub.h"

#include <iostream>

int main()
{
    short port = 5555;
    const std::string ip = "127.0.0.1";

    std::cout << "connecting to:" << ip << ":" << port << std::endl;
    auto conn = network::TcpConnectionFactory::create_connection(ip, port);

    if (conn) {
        std::cout << "connection successful" << std::endl;
    }

    return 0;
}
