#include "TcpConnectionHub.h"

#include <string>

namespace network {

TcpClientConnection* TcpConnectionHub::get_connection(const std::string& name)
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
        return false;
    }

    m_name_to_conn[name] = conn;

    return true;
}

} // close namespace network
