#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <Preload.hpp>
#include <Canvas.hpp>
#include <Donut.hpp>

using Donut::Uint;
constexpr Uint FPS = 30;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        ::std::cerr << "Usage: ./donut_3d [width] [height] [lasting_seconds]" << ::std::endl;
        return -1;
    }

    // process command parameters
    Uint width { ::std::stoul({argv[1]}) };
    Uint height { ::std::stoul({argv[2]}) };
    Uint lasting { ::std::stoul({argv[3]}) * 1000 };   // second -> milliseconds

    // create main canvas and a donut
    Donut::Canvas main_canvas(width, height);
    Donut::Donut donut(10, 5, 15, 25, main_canvas);

    main_canvas.draw(donut.getFront());

    /*
    // timer starts
    auto start_time { ::std::chrono::high_resolution_clock::now() };

    for (;;) {
        ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000 / FPS));

        if (::std::chrono::duration_cast<::std::chrono::milliseconds>(::std::chrono::high_resolution_clock::now() - start_time).count() >= lasting) {
            break;
        }
    }
     */

    return 0;
}
