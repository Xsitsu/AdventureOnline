#include "signal.hpp"

Signal::Signal()
{

}

SignalListener Signal::Connect(signal_callback callback)
{
    this->connected_funcs.push_back(callback);
    SignalListener listener(this, callback);
    return listener;
}

void Signal::Fire(SignalArgs* args)
{
    callback_iter iter = this->connected_funcs.begin();
    for (iter; iter != this->connected_funcs.end(); ++iter)
    {
        (*iter)(args);
    }
}

void Signal::DisconnectFunction(signal_callback callback)
{
    callback_iter iter = this->connected_funcs.begin();
    for (iter; iter != this->connected_funcs.end(); ++iter)
    {
        if (*iter == callback)
        {
            this->connected_funcs.erase(iter);
            return;
        }
    }
}

SignalListener::SignalListener(Signal* signal, signal_callback callback) : signal(signal), callback(callback), is_connected(true)
{

}

void SignalListener::Disconnect()
{
    if (this->is_connected)
    {
        this->is_connected = false;
        this->signal->DisconnectFunction(this->callback);
    }
}
