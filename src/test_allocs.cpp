#include <iostream>


class IMemoryManager
{
public:
    virtual void* allocate(size_t) = 0;
    virtual void free(void*) = 0;
};

class MemoryManager : public IMemoryManager
{
protected:
    struct FreeStore
    {
        FreeStore* m_next = nullptr;
    };
    void expandPoolSize() {
        void* tmp = new char[32];
        m_head = reinterpret_cast<FreeStore*>(tmp);
        m_head->m_next = nullptr;
        const static size_t POOL_SIZE = 64;
        auto cur = m_head;
        for (size_t i = 0; i < POOL_SIZE; i++)
        {
            cur->m_next = reinterpret_cast<FreeStore*>(new char[32]);
            cur = cur->m_next;
        }
        cur->m_next = nullptr;

    }
    void cleanUp();

    FreeStore* m_head = nullptr;

public:
    MemoryManager() {}
    virtual void* allocate(size_t) override {
        if (!m_head) {
            expandPoolSize();
        }
        FreeStore* head = m_head;
        m_head = head->m_next;
        return head;
    }

    virtual void free(void* deleted) override {
        FreeStore* head = reinterpret_cast<FreeStore*>(deleted);
        head->m_next = m_head;
        m_head = head;
    }
};

MemoryManager g_MemoryManager;

////////////////////////////////////////////////////////////////////
// Sample data class
class Complex
{
public:
    Complex(double r, double c) : m_r(r), m_c(c) {}
    Complex() : m_r(0), m_c(0) {}

    // added
    inline void* operator new(size_t size) {

        std::cout << "Complex new" << std::endl;
        return g_MemoryManager.allocate(size);      
    }
    inline void operator delete(void* deleted) {
        std::cout << "Complex delete" << std::endl;
        return g_MemoryManager.free(deleted);
    }
private:
    double m_r;
    double m_c;
};


////////////////////////////////////////////////////////////////////
// entry
int main(int argc, char** argv)
{
    Complex * array[1000];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 1; j++)
        {
            array[j] = new Complex(i, j);
        }
        for (int j = 0; j < 1; j++)
        {
            delete array[j];
        }
    }


    return 0;
}
