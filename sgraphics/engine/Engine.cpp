#include "Engine.hpp"

#include <string>
#include <iostream>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

#include <sgraphics/engine/impl/SdlRenderer.hpp>
#include <sgraphics/engine/impl/SdlEventer.hpp>
#include <sgraphics/engine/impl/SdlWindow.hpp>
#include <sgraphics/engine/impl/SdlSprite.hpp>
#include <sgraphics/engine/impl/SdlFont.hpp>

namespace sg
{
    Engine::Engine() = default;
    Engine::~Engine()
    {
        if (inited_)
        {
            IMG_Quit();
            SDL_Quit();
        }
    }

    bool Engine::Init(const std::string &title, int width, int hight)
    {
        if (SDL_Init(SDL_INIT_VIDEO) || !IMG_Init(IMG_INIT_PNG))
        {
            std::cerr << SDL_GetError() << '\n';
            return false;
        }

        window_ = std::make_shared<SdlWindow>(title, width, hight);
        renderer_ = std::make_shared<SdlRenderer>(window_);
        eventer_ = std::make_shared<SdlEventer>();

        inited_ = true;
        return inited_;
    }

    IWindow::Ptr Engine::GetWindow()
    {
        return inited_ ? window_ : nullptr;
    }

    IRenderer::Ptr Engine::GetRenderer()
    {
        return inited_ ? renderer_ : nullptr;
    }

    IEventer::Ptr Engine::GetEventer()
    {
        return inited_ ? eventer_ : nullptr;
    }

    ISprite::Ptr Engine::CreateSprite(const std::filesystem::path &path, const RgbType &rgb)
    {
        return inited_ ? std::make_shared<SdlSprite>(path, rgb) : nullptr;
    }

    IFont::Ptr Engine::CreateFont(const std::filesystem::path &path)
    {
        if(!inited_ || !renderer_)
            return nullptr;

        auto renderer = dynamic_cast<SdlRenderer*>(renderer_.get());
        return IFont::Ptr(new SdlFont(renderer->renderer_, path));
    }
}
