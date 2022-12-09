#pragma once

// SDL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <vector>

namespace sg {

namespace engine {


//!
//! \brief The IGame struct
//!
struct IPolygon
{
    using renderer_type = SDL_Renderer*;

    //!
    //! \brief init
    //! \param str
    //! \param info
    //! \return
    //!
    virtual renderer_type getRenderer() noexcept = 0;

    //!
    //! \brief getWidth
    //! \return
    //!
    virtual int getWidth() noexcept = 0;

    //!
    //! \brief getHight
    //! \return
    //!
    virtual int getHeight() noexcept = 0;

    //!
    //! \brief objRects
    //! \return
    //!
    virtual std::vector<SDL_Rect> getRects() noexcept = 0;

    //!
    //! \brief getEvent
    //! \return
    //!
    virtual const SDL_Event& getEvent() noexcept = 0;
};


}}
