#pragma once
#include <chrono>

namespace Pyre {

    class Time {
    public:
        Time() : m_TimePoint(Clock::now()) {}

        operator float() const { return AsSeconds(); }

        inline float AsSeconds() const {
            SecondTime time = m_TimePoint.time_since_epoch();
            return time.count();
        }
        
        inline float AsMilliseconds() const {
            MilliTime time = m_TimePoint.time_since_epoch();
            return time.count();
        }

    private:
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<Clock>;

        using SecondTime = std::chrono::duration<float>;
        using MilliTime = std::chrono::duration<float, std::milli>;
        
        TimePoint m_TimePoint;
    };

}