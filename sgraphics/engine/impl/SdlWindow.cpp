#include "SdlWindow.hpp"

namespace sg
{
    SdlWindow::SdlWindow(std::string title, int width, int hight)
        : width_(width),
          hight_(hight)
    {
        window_ = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, hight_, SDL_WINDOW_SHOWN);
        if (!window_)
        {
            throw std::runtime_error("Unable to create window");
        }
    }
    SdlWindow::~SdlWindow() { SDL_DestroyWindow(window_); }

    SDL_Window *SdlWindow::GetImpl() { return window_; }
    int SdlWindow::GetHeight() const { return hight_; }
    int SdlWindow::GetWidth() const { return width_; }
}
