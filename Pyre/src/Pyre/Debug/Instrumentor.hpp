#pragma once
#include "Pyre/Core/Base.hpp"
#include <fstream>

namespace Pyre {

    struct ProfileResult {
        const char* Name;
        long long Start, End;
        size_t ThreadID;
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

        std::string m_SessionName;
        std::ofstream m_Output;
        int m_ProfileCount = 0;

        std::mutex m_Lock;
        bool m_IsActive;
    };

    class InstrumentationTimer {
    public:
        InstrumentationTimer(const char* name);
        ~InstrumentationTimer();

        void Stop();

    private:
        using Clock = std::chrono::high_resolution_clock;

        ProfileResult m_Result;
        std::chrono::time_point<Clock> m_StartTime;
        bool m_Stopped = false;
    };

}

#ifdef PYRE_ENABLE_PROFILE
#define PYRE_PROFILE_BEGIN(name, path) ::Pyre::Instrumentor::Get().BeginSession(name, path)
#define PYRE_PROFILE_END()             ::Pyre::Instrumentor::Get().EndSession()
#define PYRE_PROFILE_SCOPE(name)       ::Pyre::InstrumentationTimer timer##__LINE__(name)
#define PYRE_PROFILE_FUNCTION()        PYRE_PROFILE_SCOPE(__FUNCSIG__)
#else
#define PYRE_PROFILE_BEGIN(name, path)
#define PYRE_PROFILE_END()
#define PYRE_PROFILE_SCOPE(name)
#define PYRE_PROFILE_FUNCTION()
#endif