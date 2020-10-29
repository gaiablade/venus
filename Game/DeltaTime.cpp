#include "DeltaTime.hpp"

namespace vn {
    DeltaTime::DeltaTime() {
        this->last = std::chrono::high_resolution_clock::now();
    }

    double DeltaTime::getDt() {
        this->now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = now - last;
        last = now;
        return duration.count();
    }
}
