//
// Created by Ivan Chien on 2022/10/28.
//

#include "Donut.hpp"

namespace Donut {

Buffer2D Donut::getFront() {
    Buffer2D output(this->m_uHeight, ::std::vector<char>(this->m_uWidth, '\0'));
    Float theta { 0 };

    const Uint width_offset { this->m_uWidth / 2 };
    const Uint height_offset { this->m_uHeight / 2 };

    constexpr Float INC { 0.05 };

    do {
        Float psi { 0 };
        theta += INC;

        Float sin_theta { ::std::sin(theta) },
              cos_theta { ::std::cos(theta) };

        [[maybe_unused]] Int z { static_cast<Int>(this->m_fR2 * sin_theta) };
        Float view_factor { static_cast<Float>(this->m_uViewerDistance) / this->m_uObjectDistance };

        do {
            psi += INC;

            Float sin_psi { ::std::sin(psi) },
                  cos_psi { ::std::cos(psi) };

            Float x { this->m_fR1 * cos_psi + this->m_fR2 * cos_theta * cos_psi };
            Float y { - this->m_fR1 * sin_psi - this->m_fR2 * cos_theta * sin_psi };

            Uint xu { static_cast<Uint>(x * view_factor + width_offset) };
            Uint yu { static_cast<Uint>(y * view_factor + height_offset) };

            output[xu][yu] = '*';

        } while (::std::islessequal(psi, TAU));
    } while (::std::islessequal(theta, TAU));

    return output;
}


}  // end of namespace Donut