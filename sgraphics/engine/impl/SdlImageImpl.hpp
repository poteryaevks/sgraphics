#pragma once

#include <string>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../IImage.hpp"

namespace sgraphics
{
    struct SdlImageImpl final : public IImage
    {
        friend class SdlRenderer;
    public:
        SDL_Surface *serface_;
        SdlImageImpl(const std::string &path) { serface_ = IMG_Load(path.c_str()); }
        ~SdlImageImpl() override { SDL_FreeSurface(serface_); }
    };
}
