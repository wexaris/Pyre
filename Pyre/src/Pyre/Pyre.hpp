#pragma once

// ----- Core -----------------------------------
#include "Pyre/Core/Base.hpp"
#include "Pyre/Core/Log.hpp"
#include "Pyre/Core/Application.hpp"
#include "Pyre/Core/Input.hpp"
#include "Pyre/Core/Layer.hpp"

#include "Pyre/ImGui/ImGuiLayer.hpp"

#include "Pyre/Debug/Instrumentor.hpp"

// ----- Utility --------------------------------
#include "Pyre/Utility/Time.hpp"
#include "Pyre/Utility/Random.hpp"

// ----- Renderer -------------------------------
#include "Pyre/Renderer/Renderer.hpp"
#include "Pyre/Renderer/Renderer2D.hpp"
#include "Pyre/Renderer/RenderCommand.hpp"

#include "Pyre/Renderer/Framebuffer.hpp"
#include "Pyre/Renderer/Texture.hpp"
#include "Pyre/Renderer/SubTexture2D.hpp"
#include "Pyre/Renderer/Shader.hpp"
#include "Pyre/Renderer/Buffer.hpp"
#include "Pyre/Renderer/VertexArray.hpp"

#include "Pyre/Renderer/Camera.hpp"
#include "Pyre/Renderer/CameraController.hpp"

// ----- Events ---------------------------------
#include "Pyre/Events/KeyCodes.hpp"
#include "Pyre/Events/MouseCodes.hpp"
#include "Pyre/Events/KeyEvents.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"
