#ifndef OBSERVER_HPP_INCLUDE
#define OBSERVER_HPP_INCLUDE

#include <iostream>

class AbstractListener
{
public:
    virtual ~AbstractListener() {}
};

template <class T>
class ListenerBase : public AbstractListener
{
public:
    virtual ~ListenerBase() {}
    virtual void Notify(T& args) const = 0;
};

class AbstractObserver
{
public:
    virtual ~AbstractObserver() {}
};

template <class T>
class Observer : public AbstractObserver
{
protected:
    std::list<ListenerBase<T>*> listeners;

    typedef typename std::list<ListenerBase<T>*>::iterator listener_iter;
    typedef typename std::list<ListenerBase<T>*>::const_iterator const_listener_iter;

public:
    Observer() {}
    ~Observer() {}

    void Connect(ListenerBase<T>* listener)
    {
        this->listeners.push_back(listener);
    }

    void Disconnect(ListenerBase<T>* listener)
    {
        listener_iter iter;
        for (iter = this->listeners.begin(); iter != this->listeners.end(); ++iter)
        {
            if (*iter == listener)
            {
                this->listeners.erase(iter);
                return;
            }
        }
    }

    void Fire(T args) const
    {
        const_listener_iter iter;
        for (iter = this->listeners.begin(); iter != this->listeners.end(); ++iter)
        {
            (*iter)->Notify(args);
        }
    }
};

#endif // OBSERVER_HPP_INCLUDE
