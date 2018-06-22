#include "network/TcpConnection.h"


int main()
{


    short port = 5555;
    const std::string ip = "127.0.0.1";

    network::TcpClientConnection conn;
    conn.init();
    conn.connect(ip, port);

    return 0;
}
