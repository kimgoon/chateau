#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <errno.h>
// net stuff

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


class ManagersBase {
public:
    bool m_stop = false;
    bool m_initialized = false;

    virtual void init();
    virtual void start();
    virtual void stop()
    {
        m_stop = true;
    }

};

class ClientManager {
public:
    std::vector<int> client_fds;


    void init()
    {
    }

    void start()
    {
        int num_of_clients = 0;

        while(!m_stop) {

            if (num_of_clients != client_fds.size()) {
                // update and reset our data
            }

            if (num_of_clients == 0) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            // check if any action on the fds

            // check for read action

            // check for write action
        }
    }

    bool m_stop = false;


};

class ConnectionManager
{
public:
    const uint16_t m_listen_port = 5555;
    const uint16_t m_max_backlog = 10;

    bool m_stop = false;

    // blocking
    bool start()
    {
        int server_fd = -1;
        int new_socket = -1;
        struct sockaddr_in address;
        int address_len = sizeof(address);
        int opt = 1;

        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == 0) {
            std::cout << "error while creating server socket" << std::endl;
            return false;
        }

        auto rc = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        if (rc) {
            std::cout << "error while setting server socket options rc:" << rc
                << " strerr:" << strerror(errno) << std::endl;
            return false;
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(m_listen_port);

        rc = bind(server_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address));
        if (rc < 0) {
            std::cout << "error while binding server socket rc:" << rc << std::endl;
            return false;
        }

        rc = listen(server_fd, m_max_backlog);
        if (rc < 0) {
            std::cout << "error while calling listen on server socket rc:" << rc << std::endl;
            return false;
        }

        while (!m_stop) {

            new_socket = accept(server_fd, reinterpret_cast<sockaddr*>(&address), reinterpret_cast<socklen_t*>(&address_len));

            if (new_socket < 0) {
                std::cout << "error while calling accept str:" << strerror(errno) << std::endl;
                return false;
            }

            std::cout << "got new client fd: " << new_socket << std::endl;
        }




        return true;
    }

private:
};

int main()
{

    std::cout << "hello from test_streamserver.cpp" << std::endl;


    std::unique_ptr<ConnectionManager> conn_mgr = std::make_unique<ConnectionManager>();
    conn_mgr->start();




    return 0;
}
