#include "pyrepch.hpp"
#include "Pyre/ImGui/ImGuiConsole.hpp"

#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>
#include <imgui.h>

namespace Pyre {

    static ImGuiConsole::Message::Color LevelColor(ImGuiConsole::Message::Level level) {
        switch (level) {
        case ImGuiConsole::Message::Level::Trace:    return { 0.75f, 0.75f, 0.75f, 1.00f }; // Gray
        case ImGuiConsole::Message::Level::Info:     return { 0.00f, 0.50f, 0.00f, 1.00f }; // Green
        case ImGuiConsole::Message::Level::Debug:    return { 0.00f, 0.50f, 0.50f, 1.00f }; // Cyan
        case ImGuiConsole::Message::Level::Warn:     return { 1.00f, 1.00f, 0.00f, 1.00f }; // Yellow
        case ImGuiConsole::Message::Level::Error:    return { 1.00f, 0.00f, 0.00f, 1.00f }; // Red
        case ImGuiConsole::Message::Level::Critical: return { 1.00f, 0.00f, 1.00f, 1.00f }; // Magenta
        case ImGuiConsole::Message::Level::Off:      return { 1.00f, 1.00f, 1.00f, 1.00f }; // White
        default: break;
        }
        PYRE_CORE_WARN("Invalid ImGui console message level");
        return { 1.00f, 1.00f, 1.00f, 1.00f }; // White
    }

    static std::string_view LevelName(ImGuiConsole::Message::Level level) {
        switch (level) {
        case ImGuiConsole::Message::Level::Trace:    return "Trace";
        case ImGuiConsole::Message::Level::Info:     return "Info";
        case ImGuiConsole::Message::Level::Debug:    return "Debug";
        case ImGuiConsole::Message::Level::Warn:     return "Warning";
        case ImGuiConsole::Message::Level::Error:    return "Error";
        case ImGuiConsole::Message::Level::Critical: return "Critical";
        case ImGuiConsole::Message::Level::Off:      return "None";
        default: break;
        }
        PYRE_CORE_WARN("Invalid ImGui console message level");
        return "Unknown"; // White
    }

    static ImGuiConsole::Message::Level HigherLevel(ImGuiConsole::Message::Level level) {
        if (level != ImGuiConsole::Message::Level::Invalid && level != ImGuiConsole::Message::Level::Off) {
            return static_cast<ImGuiConsole::Message::Level>(static_cast<int>(level) + 1);
        }
        return level;
    }

    static ImGuiConsole::Message::Level LowerLevel(ImGuiConsole::Message::Level level) {
        if (level != ImGuiConsole::Message::Level::Invalid && level != ImGuiConsole::Message::Level::Trace) {
            return static_cast<ImGuiConsole::Message::Level>(static_cast<int>(level) - 1);
        }
        return level;
    }

    ImGuiConsole::Message::Message(const std::string& msg, Level level) :
        m_Message(msg), m_Level(level)
    {}

    void ImGuiConsole::Message::OnImGuiRender() {
        Color color = LevelColor(m_Level);
        ImGui::PushStyleColor(ImGuiCol_Text, { color.r, color.g, color.b, color.a });
        ImGui::TextUnformatted(m_Message.c_str());
        ImGui::PopStyleColor();
    }

    ImGuiConsole::ImGuiConsole() {
        m_MessageBuffer.reserve(m_MessageBufferMaxSize);
    }

    void ImGuiConsole::Clear() {
        m_MessageBuffer.clear();
        m_MessageBuffer.reserve(m_MessageBufferMaxSize);
    }

    void ImGuiConsole::OnImGuiRender(bool show) {
        ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);
        ImGui::Begin("Console", &show);
        RenderHeader();
        ImGui::Separator();
        RenderMessages();
        ImGui::End();
    }

    void ImGuiConsole::AddMessage(Message&& message) {
        PYRE_CORE_ASSERT(message.m_Level != Message::Level::Invalid, "Invalid message passed to console!");

        m_MessageBuffer.push_back(MakeRef<Message>(std::move(message)));
        if (m_MessageBuffer.size() == m_MessageBufferMaxSize) {
            Clear();
        }
    }

    void ImGuiConsole::RenderHeader() {
        ImGuiStyle& style = ImGui::GetStyle();
        const float spacing = style.ItemInnerSpacing.x;

        // Text change level
        //ImGui::AlignFirstTextHeightToWidgets();
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Display");

        ImGui::SameLine(0.0f, 2.0f * spacing);

        // Buttons to quickly change level left
        if (ImGui::ArrowButton("##MessageRenderFilter_L", ImGuiDir_Left)) {
            m_Filter = LowerLevel(m_Filter);
        }

        ImGui::SameLine(0.0f, spacing);

        // Dropdown with levels
        ImGui::PushItemWidth(ImGui::CalcTextSize("Critical").x * 1.36f);
        if (ImGui::BeginCombo("##MessageRenderFilter", LevelName(m_Filter).data(), ImGuiComboFlags_NoArrowButton)) {
            for (auto level = Message::Level::Trace; level <= Message::Level::Off; level = static_cast<Message::Level>((int)level + 1)) {
                bool is_selected = (m_Filter == level);
                if (ImGui::Selectable(LevelName(level).data(), is_selected)) {
                    m_Filter = level;
                }
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::PopItemWidth();

        ImGui::SameLine(0.0f, spacing);

        // Buttons to quickly change level right
        if (ImGui::ArrowButton("##MessageRenderFilter_R", ImGuiDir_Right)) {
            m_Filter = HigherLevel(m_Filter);
        }

        ImGui::SameLine(0.0f, spacing);

        // Button for advanced settings
        ImGui::SameLine(0.0f, ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Settings").x - style.WindowPadding.x / 2.0f);
        if (ImGui::Button("Settings")) {
            ImGui::OpenPopup("SettingsPopup");
        }
        if (ImGui::BeginPopup("SettingsPopup")) {
            RenderSettings();
            ImGui::EndPopup();
        }
    }

    void ImGuiConsole::RenderSettings() {
        const float maxWidth = ImGui::CalcTextSize("Autoscroll").x * 1.1f;
        const float spacing = ImGui::GetStyle().ItemInnerSpacing.x + ImGui::CalcTextSize(" ").x;

        // Checkbox for scrolling lock
        //ImGui::AlignFirstTextHeightToWidgets();
        ImGui::Text("Autoscroll");
        ImGui::SameLine(0.0f, spacing + maxWidth - ImGui::CalcTextSize("Autoscroll").x);
        ImGui::Checkbox("##Autoscroll", &m_Autoscroll);

        ImGui::SameLine(0.0f, spacing);

        // Button to clear the console
        ImGui::SameLine(0.0f, ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Clear").x + 1.0f);
        if (ImGui::Button("Clear")) {
            ImGuiConsole::Clear();
        }

        // Slider for font scale
        //ImGui::AlignFirstTextHeightToWidgets();
        ImGui::Text("Text scale");
        ImGui::SameLine(0.0f, spacing + maxWidth - ImGui::CalcTextSize("Text scale").x);
        ImGui::PushItemWidth(maxWidth * 1.25f / 1.1f);
        ImGui::SliderFloat("##TextScale", &m_DisplayScale, 0.5f, 4.0f, "%.1f");
        ImGui::PopItemWidth();
    }

    void ImGuiConsole::RenderMessages() {
        ImGui::BeginChild("ScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        {
            ImGui::SetWindowFontScale(m_DisplayScale);

            for (auto& buffer = m_MessageBuffer.begin(); buffer != m_MessageBuffer.end(); buffer++) {
                if (!*buffer) {
                    break;
                }
                if ((*buffer)->m_Level >= m_Filter) {
                    (*buffer)->OnImGuiRender();
                }
            }

            if (m_Autoscroll && ImGui::GetScrollMaxY() > 0) {
                ImGui::SetScrollY(ImGui::GetScrollMaxY());
            }
        }
        ImGui::EndChild();
    }

}