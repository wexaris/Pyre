#include "pyrepch.hpp"
#include "Pyre/Debug/Instrumentor.hpp"

namespace Pyre {

    Instrumentor::~Instrumentor() {
        EndSession();
    }

    void Instrumentor::BeginSession(const std::string& name, const std::string& path) {
        std::lock_guard<std::mutex> lock(m_Lock);

        if (m_IsActive) {
            if (Log::GetCoreLogger()) { // In case profiling before Log initialization
                PYRE_CORE_ERROR("Cannot begin Instrumetor session '{}' while session '{}' is in progress!", name, m_SessionName);
            }
            NonLockingEndSession();
        }
        
        m_Output.open(path);
        if (m_Output.is_open()) {
            m_IsActive = true;
            m_SessionName = name;
            WriteHeader();
        }
        else {
            if (Log::GetCoreLogger()) { // In case profiling before Log initialization
                PYRE_CORE_ERROR("Instrumentor failed to open results file: ", path);
            }
        }
    }

    void Instrumentor::EndSession() {
        std::lock_guard<std::mutex> lock(m_Lock);
        NonLockingEndSession();
    }

    void Instrumentor::NonLockingEndSession() {
        if (m_IsActive) {
            WriteFooter();
            m_Output.close();
            m_ProfileCount = 0;
            m_IsActive = false;
        }
    }

    void Instrumentor::WriteHeader() {
        m_Output << "{\"otherData\": {},\"traceEvents\":[";
        m_Output.flush();
    }

    void Instrumentor::WriteProfile(const ProfileResult& result) {
        std::string res;
        
        if (m_ProfileCount++ > 0) {
            res = ",";
        }

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        res += fmt::format(
            "{{"
            "\"cat\":\"function\","
            "\"dur\":{0},"
            "\"name\":\"{1}\","
            "\"ph\":\"X\","
            "\"pid\":0,"
            "\"tid\":{2},"
            "\"ts\":{3}"
            "}}",
            result.Elapsed.count(),
            name,
            result.ThreadID,
            result.Start.count()
        );

        std::lock_guard<std::mutex> lock(m_Lock);
        if (m_IsActive) {
            m_Output << res;
            m_Output.flush();
        }
    }

    void Instrumentor::WriteFooter() {
        m_Output << "]}";
        m_Output.flush();
    }


    InstrumentationTimer::InstrumentationTimer(const char* name) :
        m_Result({ name, {}, {}, {} }),
        m_StartTime(Clock::now())
    {}

    InstrumentationTimer::~InstrumentationTimer() {
        if (!m_Stopped) {
            Stop();
        }
    }

    void InstrumentationTimer::Stop() {
        auto endTime = Clock::now();

        m_Result.Start = ProfileResult::FloatMicroseconds{ m_StartTime.time_since_epoch() };
        m_Result.Elapsed = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch() -
            std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch();
        m_Result.ThreadID = std::this_thread::get_id();

        Instrumentor::Get().WriteProfile(std::move(m_Result));
        m_Stopped = true;
    }

}