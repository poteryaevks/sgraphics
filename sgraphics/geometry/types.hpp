#pragma once

#include <sgraphics/geometry/olc.h>

namespace sg
{
    using FRectType = olc::aabb::rect<float>;
    using IntRectType = olc::aabb::rect<std::int32_t>;
    using RgbType = std::array<std::uint8_t, 4>;
    using MousePosType = std::pair<int, int>;

    // COLORS
    constexpr RgbType DARK_BLUE{0, 0, 139, 255};
    constexpr RgbType TRANSPER_DARK_BLUE{0, 0, 139, 100};
    constexpr RgbType BLUE{0, 0, 255, 255};
}
