#pragma once
#include "Pyre/Renderer/Shader.hpp"

namespace Pyre {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;

        virtual void UploadUniformInt(const std::string& name, int value) override;

        virtual void UploadUniformFloat(const std::string& name, float value) override;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) override;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) override;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;

        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

    private:
        uint32_t m_RendererID;
    };

}