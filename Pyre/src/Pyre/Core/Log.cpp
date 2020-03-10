#include "pyrepch.hpp"
#include "Pyre/Core/Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Pyre {

    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() {
        // color[timestamp] logger: message
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("PYRE");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}