#include "TcpConnection.h"
#include "util/Except.h"
#include <arpa/inet.h>
#include <iostream>

namespace network {

bool TcpClientConnection::init()
{
    m_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_fd < 0) {
        std::cout << "ERROR: unable to create socket rc=" << m_fd << std::endl;
        throw_ex(std::runtime_error, "ERROR, unable to create socket rc=" << m_fd);
    }
    return true;
}

bool TcpClientConnection::connect(const std::string& ip, short port)
{
    m_ip = ip;
    m_port = port;
    // clear out the server info
    memset(&m_server_addr, '\0', sizeof(m_server_addr));

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(port);

    auto rc = inet_pton(AF_INET, m_ip.c_str(), &m_server_addr.sin_addr);
    if (rc <= 0) {
        throw_ex(std::runtime_error, "ERROR: unable to convert ip:" << m_ip);
    }

    rc = ::connect(m_fd, reinterpret_cast<sockaddr*>(&m_server_addr), sizeof(m_server_addr));

    if (rc < 0) {
        throw_ex(std::runtime_error, "ERROR: unable to connect to ip:" << m_ip);
    }
    return true;
}

} // close namespace network
