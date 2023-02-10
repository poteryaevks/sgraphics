#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>

#include "../ITexture.hpp"

namespace sg
{
    class SdlTextureImpl final : public ITexture
    {
        friend class SdlRenderer;
    public:
        SDL_Texture *texture_;
        SdlTextureImpl(SDL_Renderer *renderer, SDL_Surface *serface)
        {
            texture_ = SDL_CreateTextureFromSurface(renderer, serface);
        }

        ~SdlTextureImpl() override { SDL_DestroyTexture(texture_); }
    };
}
