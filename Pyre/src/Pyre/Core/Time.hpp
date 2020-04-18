#pragma once
#include <chrono>

namespace Pyre {

    class Time {
    public:
        Time() : m_TimePoint(Clock::now()) {}

        operator double() const { return AsSeconds(); }

        double AsSeconds() const {
            auto time = std::chrono::time_point_cast<std::chrono::microseconds>(m_TimePoint);
            return time.time_since_epoch().count() / 1000000.0;
        }
        
        double AsMilliseconds() const {
            auto time = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_TimePoint);
            return time.time_since_epoch().count() / 1000000.0;
        }

    private:
        using Clock = std::chrono::steady_clock;

        std::chrono::time_point<Clock> m_TimePoint;
    };

}