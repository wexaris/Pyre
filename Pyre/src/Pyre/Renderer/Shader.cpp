#include "pyrepch.hpp"
#include "Pyre/Renderer/Shader.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Pyre {

    Ref<Shader> Shader::Create(const std::string& path) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLShader>(path);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLShader>(name, vertexSource, fragmentSource);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader) {
        Add(shader->GetName(), shader);
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
        PYRE_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& path) {
        auto shader = Shader::Create(path);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path) {
        auto shader = Shader::Create(path);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name) {
        PYRE_CORE_ASSERT(Exists(name), "Shader not found: \"{}\"", name);
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const {
        return m_Shaders.find(name) != m_Shaders.end();
    }

}