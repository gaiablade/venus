#include <chrono>

namespace vn {
    class DeltaTime {
    public:
        DeltaTime();
        double getDt();
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> last, now;
    };
}
