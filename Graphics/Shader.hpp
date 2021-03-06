#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "GLCall.hpp"
#include "mat4.hpp"
#include "vec4.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace vn {
    class Shader {
    public:
        //Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
        Shader() = default;

        void CreateShader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

        ~Shader() = default;

        void Use() const;

        void UniformMat4(const std::string &name, const mat4f &matrix) const;

        void UniformMat4_glm(const std::string &name, const glm::mat4 &matrix) const;

        void UniformVec4f(const std::string& name, const vec4f& vector) const;

        void UniformVec3f(const std::string& name, const vec3f& vector) const;

        void UniformFloat(const std::string& name, const float& f) const;

        // For debugging:
        vec2<std::string> DBG_GET_SHADER_FILES() const;

    private:
        std::string s_VertexShaderSource, s_FragmentShaderSource;
        int n_ShaderProgramID;
        uint32_t n_VertexShaderID, n_FragmentShaderID;

        // For debugging:
        vec2<std::string> DBG_SHADER_FILES;
    };
}

