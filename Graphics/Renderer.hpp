#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Circle.hpp"
#include "GLCall.hpp"

namespace vn {
    class Renderer {
    public:
        template<typename Drawable>
        static void Draw(const Drawable &object, int mode = GL_TRIANGLES);

    private:
    };

    template<typename Drawable>
    void Renderer::Draw(const Drawable &object, int mode) {
        object.Bind();
        GLCall(glDrawElements(mode, object.getIndices().size(), GL_UNSIGNED_INT, (const void *) nullptr));
    }
}

