#pragma once

#include <sgraphics/geometry/olc.h>

namespace sg
{
    using FloatRectType = olc::aabb::rect<float>;
    using IntRectType = olc::aabb::rect<std::int32_t>;
    using RgbType = std::array<std::uint8_t, 4>;
    using MousePosType = std::pair<int, int>;
}
