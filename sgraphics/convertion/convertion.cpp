#include <sgraphics/geometry/olc.h>

#include <sgraphics/convertion/convertion.h>

namespace sg {

namespace convertion {


SDL_FRect convert(const olc::aabb::rect<float>& alcRect)
{
    return { alcRect.pos.x, alcRect.pos.y, alcRect.size.x, alcRect.size.y};
}

SDL_Rect convert(const olc::aabb::rect<int32_t>& alcRect)
{
    return { alcRect.pos.x, alcRect.pos.y, alcRect.size.x, alcRect.size.y};
}


SDL_FPoint convert(const olc::vf2d& alcPoint)
{
    return { alcPoint.x, alcPoint.y};
}

SDL_Point convert(const olc::vi2d& alcPoint)
{
    return { alcPoint.x, alcPoint.y};
}

}}
