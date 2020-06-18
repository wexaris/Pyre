#pragma once
#include <random>

namespace Pyre {

    class Random {

    public:
        static int Int(const int min, const int max) {
            PYRE_CORE_ASSERT(min < max, "Min has to be smaller than max!");
            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(GetEngine());
        }

        static float Float(const float min, const float max) {
            return (float)Double(min, max);
        }

        static double Double(const double min, const double max) {
            PYRE_CORE_ASSERT(min < max, "Min has to be smaller than max!");
            std::uniform_real_distribution<double> distribution(min, max);
            return distribution(GetEngine());
        }

        static bool Bool() {
            std::bernoulli_distribution distribution(0.5);
            return distribution(GetEngine());
        }

    private:
        static std::mt19937& GetEngine() {
            static std::random_device seed;
            static std::mt19937 engine(seed());
            return engine;
        }
    };

}