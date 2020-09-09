//
// Created by caleb on 8/12/20.
//

#include "GLCall.hpp"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    if (GLenum error = glGetError()) {
        std::cout << "OpenGL Error #" << error << ": In "
                  << function << " In " << file << " on line " << line << std::endl;
        return false;
    }
    return true;
}
