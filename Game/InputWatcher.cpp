#include "InputWatcher.hpp"

namespace vn {
    InputWatcher::InputWatcher(Window &window) :
    window(&window)
    {
    }

    void InputWatcher::addInput(const key &id) {
        inputs.emplace_back(Input(id));
    }

    void InputWatcher::update() {
        for (auto& input: inputs) {
            if (window->IsKeyPressed(input.m_KeyID)) {
                input.m_FramesHeld++;
            } else {
                input.m_FramesHeld = 0;
            }
        }
    }

    uint32_t InputWatcher::operator[] (const key& id) {
        for (auto& input: inputs) {
            if (input.m_KeyID == id) {
                return input.m_FramesHeld;
            }
        }
        std::cout << "Input not tracked!" << std::endl;
        return 0;
    }
}