#include "Shader.hpp"

namespace vn {
    void Shader::CreateShader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile) {
        this->DBG_SHADER_FILES = { vertexShaderFile, fragmentShaderFile };
        std::ifstream vert_in(vertexShaderFile);
        std::ifstream frag_in(fragmentShaderFile);
        if (vert_in.fail()) {
            std::cerr << "Failed to open file " << vertexShaderFile << '\n';
            exit(1);
        }
        if (frag_in.fail()) {
            std::cerr << "Failed to open file " << fragmentShaderFile << '\n';
            exit(1);
        }
        std::string s;
        std::stringstream ss_VertexShaderSource, ss_FragmentShaderSource;
        while (getline(vert_in, s)) {
            ss_VertexShaderSource << s << '\n';
        }
        while (getline(frag_in, s)) {
            ss_FragmentShaderSource << s << '\n';
        }
        this->s_VertexShaderSource = ss_VertexShaderSource.str();
        this->s_FragmentShaderSource = ss_FragmentShaderSource.str();

        const char *c_VertexShaderCode = s_VertexShaderSource.c_str();
        n_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLCall(glShaderSource(n_VertexShaderID, 1, &c_VertexShaderCode, nullptr));
        GLCall(glCompileShader(n_VertexShaderID));
        {
            int result;
            glGetShaderiv(n_VertexShaderID, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE) {
                int length;
                glGetShaderiv(n_VertexShaderID, GL_INFO_LOG_LENGTH, &length);
                char *message = new char[length * sizeof(char)];
                glGetShaderInfoLog(n_VertexShaderID, length * sizeof(char), &length, message);
                std::cout << "Failed to compile vertex shader: " << message << '\n';
                delete[] message;
            }
        }

        const char *c_FragmentShaderCode = s_FragmentShaderSource.c_str();
        this->n_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        GLCall(glShaderSource(n_FragmentShaderID, 1, &c_FragmentShaderCode, nullptr));
        GLCall(glCompileShader(n_FragmentShaderID));
        {
            int result;
            glGetShaderiv(n_FragmentShaderID, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE) {
                int length;
                glGetShaderiv(n_FragmentShaderID, GL_INFO_LOG_LENGTH, &length);
                char *message = new char[length * sizeof(char)];
                glGetShaderInfoLog(n_FragmentShaderID, length * sizeof(char), &length, message);
                std::cout << "Failed to compile fragment shader: " << message << '\n';
                delete[] message;
            }
        }

        this->n_ShaderProgramID = glCreateProgram();

        GLCall(glAttachShader(n_ShaderProgramID, n_VertexShaderID));
        GLCall(glAttachShader(n_ShaderProgramID, n_FragmentShaderID));
        GLCall(glLinkProgram(n_ShaderProgramID));
        GLCall(glValidateProgram(n_ShaderProgramID));
    }

    void Shader::Use() const {
        glUseProgram(this->n_ShaderProgramID);
    }

    void Shader::UniformMat4(const std::string &name, const mat4f &matrix) const {
        int location = glGetUniformLocation(this->n_ShaderProgramID, name.c_str());
        GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const float *>(&matrix.data)));
    }

    void Shader::UniformMat4_glm(const std::string &name, const glm::mat4 &matrix) const {
        int location = glGetUniformLocation(this->n_ShaderProgramID, name.c_str());
        GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const float *>(&matrix[0][0])));
    }

    void Shader::UniformVec4f(const std::string& name, const vec4f &vector) const {
        int location = glGetUniformLocation(this->n_ShaderProgramID, name.c_str());
        GLCall(glUniform4fv(location, 1, &vector.x));
    }

    void Shader::UniformVec3f(const std::string& name, const vec3f& vector) const {
        int location = glGetUniformLocation(this->n_ShaderProgramID, name.c_str());
        GLCall(glUniform3fv(location, 1, &vector.x));
    }

    void Shader::UniformFloat(const std::string &name, const float &f) const {
        int location = glGetUniformLocation(this->n_ShaderProgramID, name.c_str());
        GLCall(glUniform1f(location, f));
    }

    vec2<std::string> Shader::DBG_GET_SHADER_FILES() const {
        return this->DBG_SHADER_FILES;
    }
}
