#pragma once

#include "../IWindow.hpp"

#include <SDL2/SDL.h>

#include <string>
#include <stdexcept>

namespace sgraphics
{
    class SdlWindow final : public IWindow
    {
        friend class SdlRenderer;
        SDL_Window *window_;
        const int width_;
        const int hight_;

    public:
        SdlWindow(std::string title, int width, int hight);
        ~SdlWindow() override;

        SDL_Window *GetImpl();

        int GetHeight() const override;
        int GetWidth() const override;
    };
}
