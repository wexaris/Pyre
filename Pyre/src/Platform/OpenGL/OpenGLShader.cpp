#include "pyrepch.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

#include <fstream>

namespace Pyre {

    static GLenum ShaderTypeFromString(const std::string& str) {
        if (str == "vertex") {
            return GL_VERTEX_SHADER;
        }
        else if (str == "fragment" || str == "pixel") {
            return GL_FRAGMENT_SHADER;
        }
        PYRE_CORE_ASSERT(false, "Invalid shader type: '{}'", str);
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& path) {
        PYRE_PROFILE_FUNCTION();

        auto lastSlash = path.find_last_of("/\\");
        lastSlash = (lastSlash == std::string::npos) ? 0 : path.find_last_of("/\\") + 1;
        auto lastDot = path.rfind('.');
        auto count = (lastDot == std::string::npos) ? path.size() - lastSlash : lastDot - lastSlash;

        m_Name = path.substr(lastSlash, count);

        Compile(Split(ReadFile(path)));
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) :
        m_Name(name)
    {
        PYRE_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaders;
        shaders[GL_VERTEX_SHADER] = vertexSource;
        shaders[GL_FRAGMENT_SHADER] = fragmentSource;
        Compile(shaders);
    }

    OpenGLShader::~OpenGLShader() {
        PYRE_PROFILE_FUNCTION();

        glDeleteProgram(m_RendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string& path) {
        PYRE_PROFILE_FUNCTION();

        std::string content;

        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (file) {
            file.seekg(0, std::ios::end);
            auto size = file.tellg();
            if (size != -1) {
                content.resize(file.tellg());
                file.seekg(0, std::ios::beg);
                file.read(&content[0], content.size());
                file.close();
            }
            else {
                PYRE_CORE_ERROR("Failed to read file: '{}'", path);
            }
        }
        else {
            PYRE_CORE_ERROR("Failed to open file: '{}'", path);
        }

        return content;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::Split(const std::string& source) {
        PYRE_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaderSources;

        const char* delimToken = "#type";
        size_t delimLength = strlen(delimToken);
        
        size_t pos = source.find(delimToken, 0);
        while (pos != std::string::npos) {

            size_t eol = source.find_first_of("\r\n", pos);
            PYRE_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
            size_t begin = pos + delimLength + 1;
            std::string type = source.substr(begin, eol - begin);
            PYRE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type: '{}'", type);

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            PYRE_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error!");
            pos = source.find(delimToken, nextLinePos);
            
            shaderSources[ShaderTypeFromString(type)] = (nextLinePos == std::string::npos) ?
                source.substr(nextLinePos) :
                source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
        PYRE_PROFILE_FUNCTION();

        GLuint program = glCreateProgram();
        PYRE_CORE_ASSERT(shaderSources.size() <= 2, "A maximum of 3 shaders are supported!");
        std::array<GLenum, 2> shaderIDs;

        int shaderIDIndex = 0;
        for (auto& shaderSource : shaderSources) {
            GLenum type = shaderSource.first;
            const std::string& sourceStr = shaderSource.second;

            GLuint shader = glCreateShader(type);

            const GLchar* source = (const GLchar*)sourceStr.c_str();
            glShaderSource(shader, 1, &source, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                auto log = std::string_view(infoLog.data());
                PYRE_CORE_ERROR("{}", log.substr(0, log.find_last_not_of("\t\n\r\f\v")));
                PYRE_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(program, shader);
            shaderIDs[shaderIDIndex++] = shader;
        }

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            for (auto id : shaderIDs) {
                glDeleteShader(id);
            }

            auto log = std::string_view(infoLog.data());
            PYRE_CORE_ERROR("{}", log.substr(0, log.find_last_not_of("\t\n\r\f\v")));
            PYRE_CORE_ASSERT(false, "Shader linking failure!");
            return;
        }

        for (auto id : shaderIDs) {
            glDetachShader(program, id);
            glDeleteShader(id);
        }

        m_RendererID = program;
    }

    void OpenGLShader::Bind() const {
        PYRE_PROFILE_FUNCTION();

        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const {
        PYRE_PROFILE_FUNCTION();

        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name, int value) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform1i(m_RendererID, loc, value);
    }

    void OpenGLShader::SetUInt(const std::string& name, unsigned int value) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform1ui(m_RendererID, loc, value);
    }

    void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform1iv(m_RendererID, loc, count, values);
    }

    void OpenGLShader::SetUIntArray(const std::string& name, unsigned int* values, uint32_t count) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform1uiv(m_RendererID, loc, count, values);
    }

    void OpenGLShader::SetFloat(const std::string& name, float value) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform1f(m_RendererID, loc, value);
    }

    void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& values) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform2f(m_RendererID, loc, values.x, values.y);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& values) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform3f(m_RendererID, loc, values.x, values.y, values.z);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& values) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniform4f(m_RendererID, loc, values.x, values.y, values.z, values.w);
    }

    void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniformMatrix3fv(m_RendererID, loc, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix) {
        PYRE_PROFILE_FUNCTION();

        GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
        glProgramUniformMatrix4fv(m_RendererID, loc, 1, GL_FALSE, glm::value_ptr(matrix));
    }

}