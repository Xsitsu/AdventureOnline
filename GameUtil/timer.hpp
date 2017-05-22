#ifndef TIMER_HPP_INCLUDE
#define TIMER_HPP_INCLUDE

#include <chrono>

#include "main.h"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
Timer
{
protected:
    uint64_t time_count;
    bool is_running;

    inline uint64_t GetNow() const;

public:
    Timer();
    ~Timer();

    void Start();
    void Stop();
    void Reset();

    double GetSeconds() const;
    double GetMiliSeconds() const;
};
#endif // TIMER_HPP_INCLUDE
