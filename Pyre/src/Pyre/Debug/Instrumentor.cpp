#include "pyrepch.hpp"
#include "Pyre/Debug/Instrumentor.hpp"

namespace Pyre {

    Instrumentor::~Instrumentor() {
        EndSession();
    }

    void Instrumentor::BeginSession(const std::string& name, const std::string& path) {
        if (!m_IsActive) {
            m_IsActive = true;
            m_SessionName = name;
            m_Output.open(path);
            WriteHeader();
        }
    }

    void Instrumentor::EndSession() {
        if (m_IsActive) {
            WriteFooter();
            m_Output.close();
            m_ProfileCount = 0;
            m_IsActive = false;
        }
    }

    void Instrumentor::WriteHeader() {
        m_Output << "{\"otherData\": {},\"traceEvents\":[";
    }

    void Instrumentor::WriteProfile(const ProfileResult& result) {
        std::lock_guard<std::mutex> lock(m_Lock);

        if (m_ProfileCount++ > 0) {
            m_Output << ",";
        }

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_Output << "{";
        m_Output << "\"cat\":\"function\",";
        m_Output << "\"dur\":" << (result.End - result.Start) << ',';
        m_Output << "\"name\":\"" << name << "\",";
        m_Output << "\"ph\":\"X\",";
        m_Output << "\"pid\":0,";
        m_Output << "\"tid\":" << result.ThreadID << ",";
        m_Output << "\"ts\":" << result.Start;
        m_Output << "}";
    }

    void Instrumentor::WriteFooter() {
        m_Output << "]}";
    }


    InstrumentationTimer::InstrumentationTimer(const char* name) :
        m_Result({ name, 0, 0, 0 }),
        m_StartTime(Clock::now())
    {}

    InstrumentationTimer::~InstrumentationTimer() {
        if (!m_Stopped) {
            Stop();
        }
    }

    void InstrumentationTimer::Stop() {
        auto endTime = Clock::now();

        m_Result.Start    = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
        m_Result.End      = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
        m_Result.ThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        Instrumentor::Get().WriteProfile(std::move(m_Result));
        m_Stopped = true;
    }

}