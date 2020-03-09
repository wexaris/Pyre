#pragma once

#include <glm/glm.hpp>

namespace Pyre {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void UploadUniformInt(const std::string& name, int values) = 0;

        virtual void UploadUniformFloat(const std::string& name, float values) = 0;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) = 0;

        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

        static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
    };

}