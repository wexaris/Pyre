#pragma once
#include "Pyre/Renderer/Shader.hpp"

#include <glad/glad.h>

namespace Pyre {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& path);
        OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;

        const std::string& GetName() const override { return m_Name; }

        virtual void SetInt(const std::string& name, int value) override;

        virtual void SetFloat(const std::string& name, float value) override;
        virtual void SetFloat2(const std::string& name, const glm::vec2& values) override;
        virtual void SetFloat3(const std::string& name, const glm::vec3& values) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& values) override;

        virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
        virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

    private:
        uint32_t m_RendererID;
        std::string m_Name;

        std::string ReadFile(const std::string& path);
        std::unordered_map<GLenum, std::string> Split(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    };

}