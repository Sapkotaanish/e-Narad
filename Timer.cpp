#include <chrono>
#include <iostream>

struct Timer {
std::chrono::time_point<std::chrono::_V2::system_clock> start , end;
    std::chrono::duration<float> duration;
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << duration.count() << " seconds taken." << std::endl;
    }
};
