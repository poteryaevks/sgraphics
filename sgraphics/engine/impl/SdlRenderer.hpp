#pragma once

#include "../IRenderer.hpp"
#include "../IWindow.hpp"

#include "sgraphics/geometry/types.hpp"

#include <memory>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

namespace sg
{   
    class SdlRenderer final : public IRenderer
    {
    private:
          SDL_Renderer *renderer_;

    public:
        SdlRenderer(IWindow::Ptr window);
        ~SdlRenderer() override;
        void ClearScreen(const RgbType &rgb) override;
        void RenderClear() override;
        void RenderPresent() override;
        ITexture::Ptr CreateTexture(IImage::Ptr) override;
        void DrawRect(const FRectType &rect, const RgbType &rbg = {0, 0, 0, 255}, bool fill = false) override;
        void DrawRect(const IntRectType &rect, const RgbType &rbg, bool fill = false) override;
        void DrawLine(const olc::vf2d &point1, const olc::vf2d &point2, const RgbType &rbg = {0, 0, 0, 255}) override;
        void DrawCircle(const olc::vi2d &point, std::int32_t radius, const RgbType &rbg = {0, 0, 0, 255}, bool fill = false) override;
        bool RenderCopy(ITexture::Ptr texture, const FRectType &src, const FRectType &dest) override;
        bool RenderCopy(ITexture::Ptr texture, const IntRectType &src, const IntRectType &dest) override;
    };
}
