#pragma once
#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>

#include <mutex>

namespace Pyre {

    class ImGuiConsole {
    public:
        struct Message {
            enum class Level : int8_t {
                Invalid = -1,
                Trace = 0,
                Debug = 1,
                Info = 2,
                Warn = 3,
                Error = 4,
                Critical = 5,
                Off = 6, // Disable logging
            };

            struct Color {
                float r, g, b, a;
            };

            Message() = default;
            Message(const std::string& msg, Level level);

            void OnImGuiRender();

            std::string m_Message;
            Level m_Level = Level::Invalid;
        };

        static ImGuiConsole& Get() {
            static ImGuiConsole instance;
            return instance;
        }
        
        void Clear();
        void OnImGuiRender(bool show);

        void AddMessage(Message&& message);

    private:
        float m_DisplayScale = 1.0f;
        uint16_t m_MessageBufferMaxSize = 200;
        std::vector<Ref<Message>> m_MessageBuffer;
        Message::Level m_Filter = Message::Level::Trace;
        bool m_Autoscroll = true;

        ImGuiConsole();
        ~ImGuiConsole() = default;

        void RenderHeader();
        void RenderSettings();
        void RenderMessages();
    };

    template<typename Mutex>
    class ImGuiConsoleSink : public spdlog::sinks::base_sink<Mutex> {
    public:
        ImGuiConsoleSink() {
            m_MessageBuffer.reserve(m_MessageBufferMaxSize);
        }
        ImGuiConsoleSink(uint8_t bufferSize) : m_MessageBufferMaxSize(bufferSize) {
            m_MessageBuffer.reserve(m_MessageBufferMaxSize);
        }
        ~ImGuiConsoleSink() = default;

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override {
            spdlog::memory_buf_t formatted;
            this->formatter_->format(msg, formatted);

            m_MessageBuffer.push_back(ImGuiConsole::Message(fmt::to_string(formatted), MessageLevel(msg.level)));
            if (m_MessageBuffer.size() == m_MessageBufferMaxSize) {
                flush_();
            }
        }

        void flush_() override {
            for (auto& message : m_MessageBuffer) {
                ImGuiConsole::Get().AddMessage(std::move(message));
            }
            m_MessageBuffer.clear();
            m_MessageBuffer.reserve(m_MessageBufferMaxSize);
        }

    private:
        uint8_t m_MessageBufferMaxSize = 1;
        std::vector<ImGuiConsole::Message> m_MessageBuffer;

        static ImGuiConsole::Message::Level MessageLevel(const spdlog::level::level_enum level) {
            switch (level) {
            case spdlog::level::level_enum::trace: return ImGuiConsole::Message::Level::Trace;
            case spdlog::level::level_enum::debug: return ImGuiConsole::Message::Level::Debug;
            case spdlog::level::level_enum::info: return ImGuiConsole::Message::Level::Info;
            case spdlog::level::level_enum::warn: return ImGuiConsole::Message::Level::Warn;
            case spdlog::level::level_enum::err: return ImGuiConsole::Message::Level::Error;
            case spdlog::level::level_enum::critical: return ImGuiConsole::Message::Level::Critical;
            case spdlog::level::level_enum::off: return ImGuiConsole::Message::Level::Off;
            default: return ImGuiConsole::Message::Level::Invalid;
            }
        }
    };

    using ImGuiConsole_mt = ImGuiConsoleSink<std::mutex>;                  // multi-threaded
    using ImGuiConsole_st = ImGuiConsoleSink<spdlog::details::null_mutex>; // single threaded

}