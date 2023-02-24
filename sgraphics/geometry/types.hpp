#pragma once

#include <sgraphics/geometry/olc.h>

namespace sgraphics
{
    using FRectType = olc::aabb::rect<float>;
    using IntRectType = olc::aabb::rect<std::int32_t>;
    using RgbType = std::array<std::uint8_t, 4>;
    using MousePosType = olc::vi2d;

    // COLORS
    constexpr RgbType DARK_BLUE{0, 0, 139, 255};
    constexpr RgbType TRANSPER_DARK_BLUE{0, 0, 139, 100};
    constexpr RgbType BLUE{0, 0, 255, 255};
    constexpr RgbType RED{255, 0, 0, 255};
    constexpr RgbType GREEN{0, 255, 0, 255};
    constexpr RgbType YELLOW{255, 255, 0, 255};
    constexpr RgbType BLACK{0, 0, 0, 255};
    constexpr RgbType WHITE{255, 255, 255, 255};
}
