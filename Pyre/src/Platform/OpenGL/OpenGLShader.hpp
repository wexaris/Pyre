#pragma once
#include "Pyre/Renderer/Shader.hpp"

namespace Pyre {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;

        void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

    private:
        uint32_t m_RendererID;
    };

}