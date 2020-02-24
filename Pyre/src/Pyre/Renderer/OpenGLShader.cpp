#include "pyrepch.hpp"
#include "Pyre/Renderer/OpenGLShader.hpp"

#include <glad/glad.h>
#include <algorithm>

namespace Pyre {

    OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = (const GLchar*)vertexSource.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            std::string log = infoLog.data();
            log.erase(log.find_last_not_of("\t\n\r\f\v") + 1);
            PYRE_CORE_ERROR("{}", log);
            PYRE_CORE_ASSERT(false, "Vertex shader compilation failure!");
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar*)fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            std::string log = infoLog.data();
            log.erase(log.find_last_not_of("\t\n\r\f\v") + 1);
            PYRE_CORE_ERROR("{}", log);
            PYRE_CORE_ASSERT(false, "Fragment shader compilation failure!");
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_ProgramID = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_ProgramID, vertexShader);
        glAttachShader(m_ProgramID, fragmentShader);

        // Link our program
        glLinkProgram(m_ProgramID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(m_ProgramID);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            std::string log = infoLog.data();
            log.erase(log.find_last_not_of("\t\n\r\f\v") + 1);
            PYRE_CORE_ERROR("{}", log);
            PYRE_CORE_ASSERT(false, "Shader linking failure!");
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_ProgramID, vertexShader);
        glDetachShader(m_ProgramID, fragmentShader);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_ProgramID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_ProgramID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

}