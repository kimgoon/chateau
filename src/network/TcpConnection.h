#pragma once

// size_t, write
#include <unistd.h>

// send
#include <sys/types.h>
#include <sys/socket.h>

// struct sockaddr_in
#include <netinet/in.h>

#include <string>

namespace network {

// define the type of connection
enum TcpConnectionType {
    Server = 0,
    Client
};

// TcpConnection is a low level abstraction of the connection layer
// It wraps the file_descriptor
class TcpConnection {

public:
    inline int send_bytes(void* buf, size_t len)
    {
        auto sent_n = send(m_fd, buf, len, 0);
        return sent_n;
    }

    inline int read_bytes(void* buf, size_t buf_size) {
        auto write_n = write(m_fd, buf, buf_size);
        return write_n;
    }

    inline const int get_fd() const { return m_fd; }


protected:
    int m_fd = 0;
};


class TcpClientConnection : public TcpConnection {
public:
    bool init();
    bool connect(const std::string& ip, short port);
    inline bool is_connected() const { return m_is_connected; }

private:
    bool m_is_connected = false;
    struct sockaddr_in m_server_addr;
    short m_port = 0;
    std::string m_ip;
};


class TcpServerConnection : public TcpConnection {
public:
    bool accept() { throw std::runtime_error(std::string(__FUNCTION__) + " Not implemented"); }
    bool listen() { throw std::runtime_error(std::string(__FUNCTION__) + " Not implemented"); }
};






} // close namespace network
