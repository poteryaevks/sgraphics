#include "SdlSprite.hpp"
#include "Engine.hpp"

#include "impl/SdlRenderer.hpp"
#include "impl/SdlImageImpl.hpp"
#include "impl/SdlTextureImpl.hpp"

#include <stdexcept>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace sg
{
    SdlSprite::SdlSprite(const std::filesystem::path &path, const RgbType &rbg)
        : img_(new SdlImageImpl(path.string()))
    {
        auto renderer = Engine::instance().GetRenderer();
        if (!renderer)
        {
            throw std::runtime_error("Unable to load background image");
        }

        texture_ = renderer->CreateTexture(img_);
        if (!texture_)
        {
            throw std::runtime_error("Unable to load background image");
        }
    }

    SdlSprite::~SdlSprite() = default;

    void SdlSprite::RenderCopy(const FRectType &src, const FRectType &dest)
    {
        auto renderer = Engine::instance().GetRenderer();
        if (!renderer)
            return;

        renderer->RenderCopy(texture_, src, dest);
    }

    void SdlSprite::RenderCopy(const IntRectType &src, const IntRectType &dest)
    {
        auto renderer = Engine::instance().GetRenderer();
        if (!renderer)
            return;

        renderer->RenderCopy(texture_, src, dest);
    }
}
