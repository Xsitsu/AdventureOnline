#ifndef SIGNAL_HPP_INCLUDE
#define SIGNAL_HPP_INCLUDE

#include <list>

#include "main.h"


template <class T>
class DLL_EXPORT SignalListenerBase
{
protected:

public:
    SignalListenerBase();

    virtual void Notify(const T& args) const = 0;
};

template <class T>
class DLL_EXPORT Signal
{
protected:
    std::list<SignalListenerBase<T>> listeners;
    typedef typename std::list<SignalListenerBase<T>>::iterator listener_iterator;
    typedef typename std::list<SignalListenerBase<T>>::const_iterator c_listener_iterator;

    Signal(const Signal<T>& copy) {}
    Signal& operator=(const Signal<T>& rhs) { return *this; }

public:
    Signal();

    void Connect(SignalListenerBase<T>* listener)
    {
        this->listeners.push_back(listener);
    }

    void Disconnect(SignalListenerBase<T>* listener)
    {
        listener_iterator iter = this->listeners.front();
        for (iter; iter != this->listeners.end(); ++iter)
        {
            if (*iter == listener)
            {
                this->listeners.erase(iter);
                return;
            }
        }
    }

    void Fire(const T& args) const
    {
        c_listener_iterator iter = this->listeners.begin();
        for (iter; iter != this->listeners.end(); ++iter)
        {
            (*iter)->Notify(args);
        }
    }
};

#endif // SIGNAL_HPP_INCLUDE
