#include "Renderer.hpp"

namespace vn {
    template<>
    void Renderer::Draw<Circle>(const Circle &object) {
        object.Bind();
        glDrawElements(GL_TRIANGLE_FAN, object.getIndices().size(), GL_UNSIGNED_INT, (const void *) nullptr);
    }
}