#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <Preload.hpp>
#include <Canvas.hpp>

using Donut::Uint;
constexpr Uint FPS = 30;

int main(int argc, char* argv[]) {

    Donut::Canvas main_canvas(50, 50);

    Uint duration = 1000 / FPS;
    Uint lasting = ::std::stoi({argv[1]}) * 1000;   // second -> milliseconds
    // timer start
    auto start_time { ::std::chrono::high_resolution_clock::now() };

    for (;;) {
        ::std::this_thread::sleep_for(::std::chrono::milliseconds(duration));

        if (::std::chrono::duration_cast<::std::chrono::milliseconds>(::std::chrono::high_resolution_clock::now() - start_time).count() >= lasting) {
            break;
        }
    }

    return 0;
}
