#pragma once

#include <atomic>
#include <array>

// N is always a power of two
template<typename T, uint32_t N=1024>
class FastQueueSPSC
{
public:
    FastQueueSPSC()
    {
    }

    // push return false if queue is full
    bool push(T* val)
    {
        if (m_tail - m_head > N) {
            return false;
        }

        auto idx = m_tail & m_mask;
        m_elements[idx] = val;

        std::atomic_thread_fence(std::memory_order_release);
        // publish tail
        m_tail++;
        return true;
    }

    T* pop()
    {
        if (m_head != m_tail) {
            auto idx = m_tail & m_mask;
            auto val = m_elements[idx];

            std::atomic_thread_fence(std::memory_order_release);
            // publish head
            ++m_head;
            return val;
        }
        return nullptr;
    }

    size_t size() const
    {
        return m_tail - m_head;
    }

private:
    std::array<T*, N> m_elements;
    uint64_t m_head = 0;
    uint64_t m_tail = 0;
    static constexpr uint32_t m_mask = N -1;
};


template<typename T, uint32_t N=1024>
class FastQueueAtomicSPSC
{
public:
    FastQueueAtomicSPSC()
    {
        m_head.store(0, std::memory_order_release);
        m_tail.store(0, std::memory_order_release);
    }

    void push(T* val)
    {
        auto idx = m_tail.load(std::memory_order_acquire) & m_mask;
        m_elements[idx] = val;
        m_tail.fetch_add(1, std::memory_order_release);
    }

    T* pop()
    {
        auto head = m_head.load(std::memory_order_acquire);
        auto tail = m_tail.load(std::memory_order_acquire);
        if (head < tail)
        {
            auto idx = head & m_mask;
            auto val = m_elements[idx];
            m_head.fetch_add(1, std::memory_order_release);
            return val;
        }
        return nullptr;
    }

    size_t size() const
    {
        return m_tail - m_head;
    }

private:
    std::array<T*, N> m_elements;
    std::atomic<uint64_t> m_head;
    std::atomic<uint64_t> m_tail;
    static constexpr uint32_t m_mask = N - 1;
};


template<typename T, uint32_t N=1024>
class FastQueueCASSPSC
{
public:
    FastQueueCASSPSC()
    {
    }

    void push(T* val)
    {
        auto cur_tail = m_tail;
    }

    T* pop()
    {
        if (m_tail == m_head) { return nullptr; }


    }

    size_t size() const
    {
        return 0;
    }

private:
    struct Node {
        Node* m_next = nullptr;
        T* m_data = nullptr;
    };

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
};
