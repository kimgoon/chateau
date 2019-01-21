#pragma once


namespace sink {

template<typename T>
class BaseSink
{
public:
    void onMessage(void* msg)
    {
        T& derived = static_cast<T&>(*this);
        derived.onMessage(msg);
    }
};


class DummySink : public BaseSink<Derived>
{
    // CRTP - allows use of derived class in base class

};

} // close namespace sink
