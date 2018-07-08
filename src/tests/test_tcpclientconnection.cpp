#include "network/TcpConnection.h"
#include "network/TcpConnectionHub.h"

#include <iostream>
#include <thread>

int main()
{
    short port = 5555;
    const std::string ip = "127.0.0.1";

    std::cout << "connecting to:" << ip << ":" << port << std::endl;
    auto conn = network::TcpConnectionFactory::create_connection(ip, port);

    if (conn) {
        std::cout << "connection successful" << std::endl;
    }

    auto hub = std::make_unique<network::TcpConnectionHub>();

    hub->add_connection("first", conn.get());

    hub->start();

    std::cout << "sleeping for 10 sec" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));

    hub->stop();

    return 0;
}
