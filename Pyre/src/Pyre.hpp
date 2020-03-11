#pragma once

// ----- Core -----------------------------------
#include "Pyre/Core/Base.hpp"
#include "Pyre/Core/Log.hpp"
#include "Pyre/Core/Time.hpp"
#include "Pyre/Core/Application.hpp"
#include "Pyre/Core/Layer.hpp"

#include "Pyre/ImGui/ImGuiLayer.hpp"

#include "Pyre/Debug/Instrumentor.hpp"

// ----- Renderer -------------------------------
#include "Pyre/Renderer/Renderer.hpp"
#include "Pyre/Renderer/Renderer2D.hpp"
#include "Pyre/Renderer/RenderCommand.hpp"

#include "Pyre/Renderer/Texture.hpp"
#include "Pyre/Renderer/Shader.hpp"
#include "Pyre/Renderer/Buffer.hpp"
#include "Pyre/Renderer/VertexArray.hpp"

#include "Pyre/Renderer/Camera.hpp"
#include "Pyre/Renderer/CameraController.hpp"

// ----- Events ---------------------------------
#include "Pyre/Events/KeyEvents.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/ApplicationEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"

// ----- Input ----------------------------------
#include "Pyre/Input/Input.hpp"
#include "Pyre/Input/KeyCodes.hpp"
#include "Pyre/Input/MouseButtonCodes.hpp"