#pragma once

#include "TcpConnection.h"
#include "util/Logger.h"
#include <unordered_map>
#include <memory>
#include <mutex>
#include <thread>

namespace network {

class TcpConnectionFactory {

public:
    TcpConnectionFactory()=delete;
    TcpConnectionFactory(const TcpConnection&)=delete;
    TcpConnectionFactory& operator=(const TcpConnection&)=delete;

    static std::unique_ptr<TcpClientConnection> create_connection(const std::string& ip, short port)
    {
        try {
            auto connection = std::make_unique<TcpClientConnection>();

            connection->init();
            connection->connect(ip, port);
            return connection;
        }
        catch(const std::runtime_error& err)
        {
            LOG_ERROR(__FUNCTION__ << ":runtime exception: " << err.what());
        }
        catch(const std::exception& err)
        {
            LOG_ERROR(__FUNCTION__ << ":exception: " << err.what());
        }
        return std::unique_ptr<TcpClientConnection>();
    }
};


class TcpConnectionHub {
public:

    using callback_type = std::function<void(void*, size_t len)>;
    TcpConnectionHub() {}

    bool init();
    bool start();
    void stop();

    TcpClientConnection* get_connection(const std::string& name) const;

    bool add_connection(const std::string& name, TcpClientConnection* conn);

    int add_receiver(callback_type cb, TcpClientConnection* conn);

    int remove_reciever(callback_type cb, TcpClientConnection* conn);
    
    int remove_all(TcpClientConnection* conn);
    
    bool is_connection_exists(const std::string& name) const;

protected:
    // utility methods
    void start_hb_thread();

    void close_all_connections();

    bool m_alive = false;
    uint8_t m_hb_interval_sec = 2;
    std::mutex m_mutex;
    std::unordered_map<std::string, TcpClientConnection*> m_name_to_conn;
    std::unordered_map<TcpClientConnection*, callback_type> m_conn_to_receiver;
    std::unique_ptr<std::thread> m_hb_thread;
};


} // close namespace network
