//
// Created by Ivan Chien on 2022/10/28.
//

#ifndef ASCII_DONUT_3D_CPP_PRELOAD_HPP
#define ASCII_DONUT_3D_CPP_PRELOAD_HPP

#include <vector>
#include <array>
#include <cfloat>
#include <cmath>

namespace Donut {

using Buffer2D = ::std::vector<::std::vector<char>>;

using Int = long;
using Uint = unsigned long;
using Float = double;

using FVec3 = ::std::array<Float, 3>;

const Float TAU = ::std::asin(1.0) * 4;

}  // end of namespace Donut

#endif //ASCII_DONUT_3D_CPP_PRELOAD_HPP
