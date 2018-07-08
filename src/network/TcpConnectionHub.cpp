#include "TcpConnectionHub.h"
#include "util/except.h"
#include <string>
#include <thread>

namespace network {

bool TcpConnectionHub::init()
{
    return true;
}

bool TcpConnectionHub::start()
{
    m_alive = true;
    return true;
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

    while(m_alive)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        // loop through all connections and send a heartbeat msg

    }
}


} // close namespace network
