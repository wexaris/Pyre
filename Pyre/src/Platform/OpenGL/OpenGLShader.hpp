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

        virtual void UploadUniformInt(const std::string& name, int value) override;

        virtual void UploadUniformFloat(const std::string& name, float value) override;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) override;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) override;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;

        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

    private:
        uint32_t m_RendererID;
        std::string m_Name;

        std::string ReadFile(const std::string& path);
        std::unordered_map<GLenum, std::string> Split(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    };

}