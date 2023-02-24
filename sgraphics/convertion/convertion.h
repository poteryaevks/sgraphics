#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <array>

#include <sgraphics/geometry/olc.h>

namespace sgraphics {

namespace convertion {

//!
//! \brief convert
//! \param alcRect
//! \return
//!
SDL_FRect convert(const olc::aabb::rect<float>& alcRect);

//!
//! \brief convert
//! \param alcRect
//! \return
//!
SDL_Rect convert(const olc::aabb::rect<int32_t>& alcRect);

//!
//! \brief convert
//! \param alcPoint
//! \return
//!
SDL_FPoint convert(const olc::vf2d& alcPoint);


//!
//! \brief convert
//! \param alcPoint
//! \return
//!
SDL_Point convert(const olc::vi2d& alcPoint);


}}
