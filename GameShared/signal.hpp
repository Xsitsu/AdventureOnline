#ifndef SIGNAL_HPP_INCLUDE
#define SIGNAL_HPP_INCLUDE

#include <list>

#include "main.h"

struct DLL_EXPORT SignalArgs
{
    virtual ~SignalArgs() {}
};

typedef DLL_EXPORT void (*signal_callback)(const SignalArgs* args);
typedef std::list<signal_callback>::iterator callback_iter;

class SignalListener;

class DLL_EXPORT Signal
{
friend class SignalListener;

protected:
    std::list<signal_callback> connected_funcs;

    void DisconnectFunction(signal_callback callback);

    Signal(const Signal& copy) {}
    Signal& operator=(const Signal& rhs) {}

public:
    Signal();

    SignalListener Connect(signal_callback callback);
    void Fire(SignalArgs* args);
};

class DLL_EXPORT SignalListener
{
protected:
    bool is_connected;
    signal_callback callback;
    Signal* signal;

public:
    SignalListener(Signal* signal, signal_callback callback);
    void Disconnect();

};

#endif // SIGNAL_HPP_INCLUDE
