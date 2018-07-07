#pragma once

#include "TcpConnection.h"


#include <unordered_map>
#include <memory>

namespace network {

class TcpConnectionFactory {

public:
    TcpConnectionFactory()=delete;
    TcpConnectionFactory(const TcpConnection&)=delete;
    TcpConnectionFactory& operator=(const TcpConnection&)=delete;

    static std::unique_ptr<TcpClientConnection> create_connection(const std::string& ip, short port)
    {
        auto connection = std::make_unique<TcpClientConnection>();
        connection->init();
        connection->connect(ip, port);
        return connection;
    }
};


class TcpConnectionHub {
public:

    using callback_type = std::function<void(void*, size_t len)>;
    TcpConnectionHub() {}

    TcpClientConnection* get_connection(const std::string& name);

    bool add_connection(const std::string& name, TcpClientConnection* conn);

    int add_receiver(callback_type cb, TcpClientConnection* conn);
    int remove_reciever(callback_type cb, TcpClientConnection* conn);
    int remove_all(TcpClientConnection* conn);

protected:
    std::unordered_map<std::string, TcpClientConnection*> m_name_to_conn;
    std::unordered_map<TcpClientConnection*, callback_type> m_conn_to_receiver;
};


} // close namespace network
