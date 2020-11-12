#pragma once
#include <vector>
#include "../Graphics/Window.hpp"

namespace vn {
    struct Input {
        key m_KeyID;
        uint32_t m_FramesHeld;
        Input(const key& id) :
        m_KeyID(id), m_FramesHeld(0)
        {
        }
    };

    class InputWatcher {
    public:
        InputWatcher(Window& window);
        void addInput(const key& id);
        void update();
        uint32_t operator[] (const key& id);
    private:
        Window* window;
        std::vector<Input> inputs;
    };
}
