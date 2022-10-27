//
// Created by Ivan Chien on 2022/10/28.
//

#include "Canvas.hpp"
#include <cassert>

namespace Donut {

static void putchar(char ch) {
    ::std::cout << ch << ' ' << ::std::endl;
}

void Canvas::draw(const Buffer2D& b2d) {
    this->clear();
    assert(b2d.size() == this->m_uHeight);
    assert(b2d[0].size() == this->m_uWidth);

    for (const auto& v : b2d) {
        for (const auto& b : v) {
            if (b == '\0') {
                putchar(' ');
            } else {
                putchar(b);
            }
        }
        ::std::endl(::std::cout);
    }
}

}  // end of namespace Donut
