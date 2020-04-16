#include "pyrepch.hpp"
#include "Pyre/Core/Log.hpp"
#include "Pyre/ImGui/ImGuiConsole.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Pyre {

    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::Init(const std::string& path) {

        // Create sinks
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<ImGuiConsole_mt>()); // ImGui console
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>()); // VS debug console
        sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(path, true)); // log file

        sinks[0]->set_pattern("%^[%T] %n: %v%$");
        sinks[1]->set_pattern("%^[%T] %n: %v%$");
        sinks[2]->set_pattern("[%T] [%1] %n: %v");

        // Create loggers
        s_CoreLogger = std::make_shared<spdlog::logger>("PYRE", sinks.begin(), sinks.end());
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);

        s_ClientLogger = std::make_shared<spdlog::logger>("APP", sinks.begin(), sinks.end());
        spdlog::register_logger(s_ClientLogger);
        s_ClientLogger->set_level(spdlog::level::trace);
        s_ClientLogger->flush_on(spdlog::level::trace);
    }
}