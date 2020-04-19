#pragma once
#include <chrono>

namespace Pyre {

    struct Time {
        std::chrono::time_point<std::chrono::steady_clock> Point;

        Time() : Point(std::chrono::steady_clock::now()) {}

        long long AsSeconds() const {
            return std::chrono::time_point_cast<std::chrono::seconds>(Point).time_since_epoch().count();
        }

        long long AsMilliseconds() const {
            return std::chrono::time_point_cast<std::chrono::milliseconds>(Point).time_since_epoch().count();
        }

        long long AsMicroseconds() const {
            return std::chrono::time_point_cast<std::chrono::microseconds>(Point).time_since_epoch().count();
        }

        long long AsNanoseconds() const {
            return std::chrono::time_point_cast<std::chrono::nanoseconds>(Point).time_since_epoch().count();
        }

        double AsSecondsf() const {
            return AsNanoseconds() * 1E-9;
        }

        double AsMillisecondsf() const {
            return AsNanoseconds() * 1E-6;
        }

        double AsMicrosecondsf() const {
            return AsNanoseconds() * 1E-3;
        }

    };

}