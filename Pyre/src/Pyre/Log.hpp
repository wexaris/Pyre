#pragma once
#include "Core.hpp"
#include <spdlog/spdlog.h>
#include <memory>

namespace spdlog {
    class logger;
}

namespace Pyre {

    class PYRE_API Log {
    
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

#define PYRE_CORE_TRACE(...)   ::Pyre::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PYRE_CORE_INFO(...)    ::Pyre::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PYRE_CORE_WARN(...)    ::Pyre::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PYRE_CORE_ERROR(...)   ::Pyre::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PYRE_CORE_FATAL(...)   ::Pyre::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define PYRE_CLIENT_TRACE(...) ::Pyre::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PYRE_CLIENT_INFO(...)  ::Pyre::Log::GetClientLogger()->info(__VA_ARGS__)
#define PYRE_CLIENT_WARN(...)  ::Pyre::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PYRE_CLIENT_ERROR(...) ::Pyre::Log::GetClientLogger()->error(__VA_ARGS__)
#define PYRE_CLIENT_FATAL(...) ::Pyre::Log::GetClientLogger()->critical(__VA_ARGS__)