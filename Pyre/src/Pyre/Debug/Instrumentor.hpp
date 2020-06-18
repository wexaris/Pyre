#pragma once
#include "Pyre/Core/Base.hpp"
#include <fstream>

namespace Pyre {

    struct ProfileResult {
        using FloatMicroseconds = std::chrono::duration<double, std::micro>;

        const char* Name;
        FloatMicroseconds Start;
        std::chrono::microseconds Elapsed;
        std::thread::id ThreadID;
    };

    class Instrumentor {
    public:
        void BeginSession(const std::string& name, const std::string& path = "results.json");
        void EndSession();

        void WriteHeader();
        void WriteProfile(const ProfileResult& result);
        void WriteFooter();

        static Instrumentor& Get() {
            static Instrumentor instrumentor;
            return instrumentor;
        }

    private:
        Instrumentor() = default;
        ~Instrumentor();

        void NonLockingEndSession();

        std::string* m_Session = nullptr;
        std::ofstream m_Output;
        std::mutex m_Lock;
    };

    class InstrumentationTimer {
    public:
        InstrumentationTimer(const char* name);
        ~InstrumentationTimer();

        void Stop();

    private:
        using Clock = std::chrono::steady_clock;

        ProfileResult m_Result;
        std::chrono::time_point<Clock> m_StartTime;
        bool m_Stopped = false;
    };


    namespace InstrumentorUtils {

        template<size_t N>
        struct ResultString {
            char Data[N];
        };

        template<size_t N, size_t K>
        constexpr ResultString<N> CleanSignature(const char(&string)[N], const char(&remove)[K]) {
            ResultString<N> result = {};

            size_t srcIndex = 0;
            size_t dstIndex = 0;
            while (srcIndex < N) {
                size_t matchIndex = 0;
                while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && string[srcIndex + matchIndex] == remove[matchIndex])
                    matchIndex++;
                if (matchIndex == K - 1)
                    srcIndex += matchIndex;
                result.Data[dstIndex++] = string[srcIndex] == '"' ? '\'' : string[srcIndex];
                srcIndex++;
            }
            return result;
        }

    }
}

#ifdef PYRE_ENABLE_PROFILE
    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
        #define PYRE_FUNCSIG __PRETTY_FUNCTION__
    #elif defined(__DMC__) && (__DMC__ >= 0x810)
        #define PYRE_FUNCSIG __PRETTY_FUNCTION__
    #elif defined(__FUNCSIG__) || (_MSC_VER)
        #define PYRE_FUNCSIG __FUNCSIG__
    #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
        #define PYRE_FUNCSIG __FUNCTION__
    #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
        #define PYRE_FUNCSIG __FUNC__
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
        #define PYRE_FUNCSIG __func__
    #elif defined(__cplusplus) && (__cplusplus >= 201103)
        #define PYRE_FUNCSIG __func__
    #else
        #define PYRE_FUNCSIG "Function signature unknown!"
    #endif

    #define PYRE_PROFILE_BEGIN(name, path) ::Pyre::Instrumentor::Get().BeginSession(name, path)
    #define PYRE_PROFILE_END()             ::Pyre::Instrumentor::Get().EndSession()
    #define PYRE_PROFILE_SCOPE(name)       constexpr auto funcSig = ::Pyre::InstrumentorUtils::CleanSignature(name, "__cdecl ");\
                                           ::Pyre::InstrumentationTimer timer##__LINE__(funcSig.Data)
    #define PYRE_PROFILE_FUNCTION()        PYRE_PROFILE_SCOPE(PYRE_FUNCSIG)
#else
    #define PYRE_PROFILE_BEGIN(name, path)
    #define PYRE_PROFILE_END()
    #define PYRE_PROFILE_SCOPE(name)
    #define PYRE_PROFILE_FUNCTION()
#endif