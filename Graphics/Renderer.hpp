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
        static void Draw(const Drawable &object);

    private:
    };

    template<typename Drawable>
    void Renderer::Draw(const Drawable &object) {
        object.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, object.getIndices().size(), GL_UNSIGNED_INT, (const void *) nullptr));
    }
}

