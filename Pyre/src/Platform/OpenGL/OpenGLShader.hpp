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

        void SetInt(const std::string& name, int value) override;
        void SetUInt(const std::string& name, unsigned int value) override;
        void SetIntArray(const std::string& name, int* values, uint32_t count) override;
        void SetUIntArray(const std::string& name, unsigned int* values, uint32_t count) override;

        void SetFloat(const std::string& name, float value) override;
        void SetFloat2(const std::string& name, const glm::vec2& values) override;
        void SetFloat3(const std::string& name, const glm::vec3& values) override;
        void SetFloat4(const std::string& name, const glm::vec4& values) override;

        void SetMat3(const std::string& name, const glm::mat3& matrix) override;
        void SetMat4(const std::string& name, const glm::mat4& matrix) override;

    private:
        uint32_t m_RendererID = 0;
        std::string m_Name;

        std::string ReadFile(const std::string& path);
        std::unordered_map<GLenum, std::string> Split(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    };

}