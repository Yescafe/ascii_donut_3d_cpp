//
// Created by Ivan Chien on 2022/10/28.
//

#ifndef ASCII_DONUT_3D_CPP_CANVAS_HPP
#define ASCII_DONUT_3D_CPP_CANVAS_HPP

#include <Preload.hpp>
#include <iostream>
#include <vector>

namespace Donut {

class Canvas {
public:
    Canvas() {
        // hide terminal cursor
        ::std::cout << "\x1b[?25l" << ::std::endl;

        clear();
    }

    explicit Canvas(Uint width, Uint height) : Canvas() {
        this->m_uWidth = width;
        this->m_uHeight = height;
    }

    ~Canvas() {
        // show terminal cursor
        ::std::cout << "\x1b[?25h" << ::std::endl;
    }

public:
    Uint getMUWidth() const {
        return m_uWidth;
    }

    Uint getMUHeight() const {
        return m_uHeight;
    }

public:
    void draw(const Buffer2D& b2d);
    void clear() {
        // clean screen, Windows maybe use OS `cls`?
        ::std::cout << "\x1b[2J" << ::std::endl;
    }

private:
    Uint m_uWidth, m_uHeight;
};

}  // end of namespace Donut


#endif //ASCII_DONUT_3D_CPP_CANVAS_HPP
