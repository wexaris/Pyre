#pragma once
#include <chrono>

namespace Pyre {

    class Time {
    public:
        Time() : m_TimePoint(Clock::now()) {}

        operator float() const { return AsSeconds(); }

        float AsSeconds() const {
            auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(m_TimePoint);
            return time.time_since_epoch().count() / 1000.f;
        }
        
        float AsMilliseconds() const {
            auto time = std::chrono::time_point_cast<std::chrono::microseconds>(m_TimePoint);
            return time.time_since_epoch().count() / 1000.f;
        }

    private:
        using Clock = std::chrono::steady_clock;

        std::chrono::time_point<Clock> m_TimePoint;
    };

}