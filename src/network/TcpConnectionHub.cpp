#include "TcpConnectionHub.h"
#include "util/Except.h"
#include <string>
#include <iostream>

namespace network {

bool TcpConnectionHub::init()
{
    return true;
}

bool TcpConnectionHub::start()
{
    m_alive = true;
    std::cout << "Starting tcpconnectionhub" << std::endl;

    m_hb_thread = std::make_unique<std::thread>(&TcpConnectionHub::start_hb_thread, this);
    return true;
}

void TcpConnectionHub::stop()
{
    std::cout << "Stopping tcpconnectionhub" << std::endl;
    m_alive = false;
}

TcpClientConnection* TcpConnectionHub::get_connection(const std::string& name) const
{
    auto it = m_name_to_conn.find(name);
    if (it == m_name_to_conn.end()) {
        return nullptr;
    }
    return it->second;
}

bool TcpConnectionHub::add_connection(const std::string& name, TcpClientConnection* conn)
{
    if (name.empty() || m_name_to_conn.count(name) > 0) {
        throw_ex(std::runtime_error, "Unable to add connection:"<<name);
        return false;
    }

    m_name_to_conn[name] = conn;

    return true;
}

bool TcpConnectionHub::is_connection_exists(const std::string& name) const
{
    if (m_name_to_conn.count(name)) {
        return true;
    }
    return false;
}

void TcpConnectionHub::start_hb_thread()
{

    int seq_no = 0;
    while(m_alive)
    {
        std::this_thread::sleep_for(std::chrono::seconds(m_hb_interval_sec));
        // loop through all connections and send a heartbeat msg
        std::string hb_msg = "HB:";
        hb_msg += std::to_string(seq_no);

        {
            std::lock_guard<std::mutex> lock(m_mutex);
            for(auto& pare : m_name_to_conn)
            {
                auto& name = pare.first;
                auto& conn = pare.second;

                std::cout << "sending hb for " << name << " msg:'" << hb_msg.c_str()
                    << "' size:" << hb_msg.size() << std::endl;

                conn->send_bytes(static_cast<const void*>(hb_msg.c_str()), hb_msg.size());
            }
        }
    }
}


} // close namespace network
