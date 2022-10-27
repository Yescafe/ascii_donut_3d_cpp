//
// Created by Ivan Chien on 2022/10/28.
//

#ifndef ASCII_DONUT_3D_CPP_DONUT_HPP
#define ASCII_DONUT_3D_CPP_DONUT_HPP

#include <Preload.hpp>
#include <Canvas.hpp>

namespace Donut {

class Donut {
public:
    Donut(Float r1, Float r2, Uint vd, Uint od, const Canvas& canvas) : Donut() {
        this->m_fR1 = r1;
        this->m_fR2 = r2;
        this->m_uViewerDistance = vd;
        this->m_uObjectDistance = od;
        this->m_uWidth = canvas.getWidth();
        this->m_uHeight = canvas.getHeight();
    }

private:
    Donut() {
        this->m_fDelta = 0;
        this->m_fARadian = 0;
        this->m_fv3LightSource = {1, 0, 1};
    }

public:
    Buffer2D getFront();

private:
    Uint m_uWidth, m_uHeight;
    Float m_fR1, m_fR2;
    Uint m_uViewerDistance, m_uObjectDistance;
    Float m_fDelta, m_fARadian;
    FVec3 m_fv3LightSource;

private:
    Float dot_product(const FVec3 a, const FVec3& b) {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }
};

} // end of namespace Donut


#endif //ASCII_DONUT_3D_CPP_DONUT_HPP
