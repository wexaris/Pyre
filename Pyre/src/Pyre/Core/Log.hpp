#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>

namespace Pyre {

    class Log { 
    public:
        static void Init();

        inline static Ref<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger; }
        inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };

}

#define FMT(...) ::fmt::format(__VA_ARGS__)

#define PYRE_CORE_TRACE(...) ::Pyre::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PYRE_CORE_INFO(...)  ::Pyre::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PYRE_CORE_WARN(...)  ::Pyre::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PYRE_CORE_ERROR(...) ::Pyre::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PYRE_CORE_CRITICAL(...) ::Pyre::Log::GetCoreLogger()->critical(__VA_ARGS__);

#define PYRE_TRACE(...) ::Pyre::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PYRE_INFO(...)  ::Pyre::Log::GetClientLogger()->info(__VA_ARGS__)
#define PYRE_WARN(...)  ::Pyre::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PYRE_ERROR(...) ::Pyre::Log::GetClientLogger()->error(__VA_ARGS__)
#define PYRE_CRITICAL(...) ::Pyre::Log::GetClientLogger()->critical(__VA_ARGS__);