//
// Created by Ivan Chien on 2022/10/28.
//

#include "Donut.hpp"

namespace Donut {

constexpr Float INC { 0.05 };

Buffer2D Donut::getFront() {
    Buffer2D output(this->m_uHeight, ::std::vector<char>(this->m_uWidth, '\0'));
    Float theta { 0 };

    Float view_factor { static_cast<Float>(this->m_uViewerDistance) / this->m_uObjectDistance };

    const Uint width_offset { this->m_uWidth / 2 };
    const Uint height_offset { this->m_uHeight / 2 };

    do {
        Float psi { 0 };
        theta += INC;

        Float sin_theta { ::std::sin(theta) },
              cos_theta { ::std::cos(theta) };

        [[maybe_unused]] Int z { static_cast<Int>(this->m_fR2 * sin_theta) };

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

Buffer2D Donut::getNextFrameXYRotation() {
    ::std::vector<::std::vector<Int>> z_max(this->m_uHeight, ::std::vector<Int>(this->m_uWidth, -114514));
    Buffer2D output(this->m_uHeight, ::std::vector<char>(this->m_uWidth, '\0'));
    Float theta { 0 };

    this->m_fDelta += INC;
    Float sin_delta { ::std::sin(this->m_fDelta) },
          cos_delta { ::std::cos(this->m_fDelta) };
    this->m_fPhi += INC;
    Float sin_phi { ::std::sin(this->m_fPhi) },
          cos_phi { ::std::cos(this->m_fPhi) };

    Float view_factor { static_cast<Float>(this->m_uViewerDistance) / this->m_uObjectDistance };

    const Uint width_offset { this->m_uWidth / 2 };
    const Uint height_offset { this->m_uHeight / 2 };

    do {
        Float psi { 0 };
        theta += INC;

        Float sin_theta { ::std::sin(theta) },
              cos_theta { ::std::cos(theta) };

        do {
            psi += INC;

            Float sin_psi { ::std::sin(psi) },
                  cos_psi { ::std::cos(psi) };

            Float x { cos_phi * (this->m_fR1 * cos_psi + this->m_fR2 * cos_theta * cos_psi) -
                      sin_phi * (this->m_fR2 * sin_theta + this->m_fR1 * sin_psi * sin_delta +
                                this->m_fR2 * cos_theta * sin_psi * sin_delta)};
            Float y { this->m_fR2 * sin_theta * sin_delta - this->m_fR1 * sin_psi * cos_delta -
                        this->m_fR2 * cos_theta * sin_psi * cos_delta};
            Float z { sin_phi * (this->m_fR1 * cos_psi + this->m_fR2 * cos_theta * cos_psi) +
                      cos_phi * (this->m_fR2 * sin_theta + this->m_fR1 * sin_psi * sin_delta +
                                 this->m_fR2 * cos_theta * sin_psi * sin_delta)};

            Uint xu { static_cast<Uint>(x * view_factor + width_offset) };
            Uint yu { static_cast<Uint>(y * view_factor + height_offset) };

//#define ENABLE_LUMI
#ifndef ENABLE_LUMI
            output[xu][yu] = '*';
#else
            FVec3 n {
                (cos_theta * cos_psi) * cos_phi - (sin_theta * cos_delta + cos_theta * sin_psi * sin_delta) * sin_phi,
                (cos_theta * cos_psi) * sin_phi + (sin_theta * cos_delta + cos_theta * sin_psi * sin_delta) * cos_phi,
                sin_theta * sin_delta - cos_theta * sin_psi * cos_delta,
            };
            auto lumi = Donut::dot_product(n, this->m_fv3LightSource) * 8;
            if (static_cast<Int>(z) > z_max[xu][yu]) {
                z_max[xu][yu] = static_cast<Int>(z);
                if (lumi < 0) {
                    output[xu][yu] = ' ';
                } else {
                    output[xu][yu] = LUMI[static_cast<Uint>(lumi)];
                }
            }
#endif
        } while (::std::islessequal(psi, TAU));
    } while (::std::islessequal(theta, TAU));

    return output;
}


}  // end of namespace Donut