#pragma once

// ----- Core -----------------------------------
#include "Pyre/Core/Base.hpp"
#include "Pyre/Core/Log.hpp"
#include "Pyre/Core/Application.hpp"
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

// ----- Input ----------------------------------
#include "Pyre/Input/Input.hpp"
#include "Pyre/Input/KeyCodes.hpp"
#include "Pyre/Input/MouseCodes.hpp"
#include "Pyre/Input/KeyEvents.hpp"
#include "Pyre/Input/MouseEvents.hpp"
#include "Pyre/Input/WindowEvents.hpp"
