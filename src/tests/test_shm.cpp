#include <iostream>
#include <thread>
#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

static const constexpr size_t SHM_SIZE = 2048; // 2K

int main(int argc, char** argv)
{
    int mode = 0;
    if (argc > 1) {
        std::string sn(argv[1]);
        std::cout << "sn:" << sn << std::endl;
        mode = 1;
    }

    key_t key = ftok("/tmp/testshm", 'R');
    if (key == -1) {
        std::cout << "bad result from ftok:" << key << std::endl;
        return -1;
    }

    int shm_id = shmget(key, SHM_SIZE, mode == 1 ? 0644|IPC_CREAT : 0);
    if (shm_id == -1) {
        std::cout << "unable to create space:" << shm_id << std::endl;
        return -1;
    }

    char* data = reinterpret_cast<char*>(shmat(shm_id, nullptr, 0));
    if (data == reinterpret_cast<char*>(-1)) {
        std::cout << "unable to attach memory segment" << std::endl;
        return -1;
    }

    static const std::string value("HELLO.WORLD");
    if (mode == 1) {
        std::cout << "copied data in" << std::endl;
        memcpy(data, value.c_str(),value.size());
    }
    else {
        char buffer[23];
        memcpy(buffer, data, value.size());
        buffer[value.size()] = '\0';
        std::cout << "read:" << buffer << std::endl;
    }

    if (mode == 1) {
        std::cout << "going to sleep" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
        int res = shmdt(data);
        if (res == -1) {
            std::cout << "failed to detach memory segment" << std::endl;
            return -1;
        }

        res = shmctl(shm_id, IPC_RMID, 0);
        if (res == -1) {
            std::cout << "failed to remove memory segment" << std::endl;
            return -1;
        }
    }


    return 0;
}
