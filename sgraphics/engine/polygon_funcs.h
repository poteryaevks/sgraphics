#pragma once

#include <array>

#include <sgraphics/geometry/olc.h>
#include <sgraphics/convertion/convertion.h>
#include <sgraphics/engine/polygon.h>

// SDL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

namespace sg {

namespace engine {


//!
//! \brief clearScreen
//! \param rgb
//!
void clearScreen(std::array<uint8_t, 4> rgb = {255, 255, 255, 255});

//!
//! \brief getWidth
//! \return
//!
int getWidth();


//!
//! \brief getHeight
//! \return
//!
int getHeight();

//!
//! \brief getMousePosition
//! \return
//!
std::pair<int, int> getMousePosition();


//!
//! \brief mousePressed
//! \return
//!
bool mousePressed();


//!
//! \brief drawRect
//! \param renderer
//! \param rect
//!
void drawRect(const olc::aabb::rect<float>& rect,
              const std::array<uint8_t, 4>& rbg = {0, 0, 0, 255},
              bool fill = false);

//!
//! \brief drawRect
//! \param rect
//! \param rbg
//!
void drawRect(const olc::aabb::rect<std::int32_t>& rect,
              const std::array<uint8_t, 4>& rbg,
              bool fill = false);

//!
void drawLine(const olc::vf2d& point1,
              const olc::vf2d& point2,
              const std::array<uint8_t, 4>& rbg = {0, 0, 0, 255});

//!
void drawCircle(const olc::vi2d& point,
                int32_t radius,
                const std::array<uint8_t, 4>& rbg = {0, 0, 0, 255},
                bool fill = false
                );


//!
//! \brief A_button
//! \return
//!
bool A_DOWN();

//!
//! \brief D_button
//! \return
//!
bool D_DOWN();

//!
//! \brief S_button
//! \return
//!
bool S_DOWN();


//!
//! \brief W_button
//! \return
//!
bool W_DOWN();

//!
//! \brief A_button
//! \return
//!
bool A_UP();

//!
//! \brief D_button
//! \return
//!
bool D_UP();

//!
//! \brief S_button
//! \return
//!
bool S_UP();


//!
//! \brief W_button
//! \return
//!
bool W_UP();

//!
//! \brief getEvent
//! \return
//!
const SDL_Event &getEvent();

}}

