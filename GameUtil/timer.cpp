#include "timer.hpp"

Timer::Timer() : time_count(0), is_running(false)
{

}

Timer::~Timer()
{

}

uint64_t Timer::GetNow() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Timer::Start()
{
    this->time_count = this->GetNow() - this->time_count;

    this->is_running = true;
}

void Timer::Stop()
{
    uint64_t current = this->GetMiliSeconds();

    this->is_running = false;

    this->time_count = current;
}

void Timer::Reset()
{
    if (this->is_running)
    {
        this->time_count = this->GetNow();
    }
    else
    {
        this->time_count = 0;
    }
}

double Timer::GetSeconds() const
{
    return this->GetMiliSeconds() / 1000;
}

double Timer::GetMiliSeconds() const
{
    if (this->is_running)
    {
        return this->GetNow() - this->time_count;
    }
    else
    {
        return this->time_count;
    }
}
