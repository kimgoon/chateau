#include "network/TcpConnection.h"
#include "network/TcpConnectionHub.h"
#include "util/Logger.h"
#include <iostream>
#include <thread>

int main()
{
    short port = 5555;
    const std::string ip = "127.0.0.1";

    LOG_INFO("connecting to:" << ip << ":" << port);
    auto conn = network::TcpConnectionFactory::create_connection(ip, port);

    if (conn) {
        LOG_INFO("connection successful");
    }
    else {
        LOG_FATAL("connection not available");
        return -1;
    }

    auto hub = std::make_unique<network::TcpConnectionHub>();

    hub->add_connection("first", conn.get());

    hub->start();

    LOG_INFO("sleeping for 10 sec");
    std::this_thread::sleep_for(std::chrono::seconds(10));

    hub->stop();

    return 0;
}
