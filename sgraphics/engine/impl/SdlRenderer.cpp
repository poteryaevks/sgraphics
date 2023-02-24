#include "SdlRenderer.hpp"
#include "SdlWindow.hpp"
#include "SdlImageImpl.hpp"
#include "SdlTextureImpl.hpp"

#include "sgraphics/convertion/convertion.h"
#include "sgraphics/geometry/types.hpp"

#include <stdexcept>

namespace
{
    void SetPixel(SDL_Renderer *renderer, const olc::vf2d &point, const sgraphics::RgbType &rbg)
    {
        SDL_SetRenderDrawColor(renderer, rbg[0], rbg[1], rbg[2], rbg[3]);
        SDL_RenderDrawPoint(renderer, point.x, point.y);
    }

    void DrawCircle(SDL_Renderer *renderer, const olc::vi2d &point, std::int32_t radius, const sgraphics::RgbType &rgb)
    {
        // if the first pixel in the screen is represented by (0,0) (which is in sdl)
        // remember that the beginning of the circle is not in the middle of the pixel
        // but to the left-top from it:
        double error = (double)-radius;
        double x = (double)radius - 0.5;
        double y = (double)0.5;
        double cx = point.x - 0.5;
        double cy = point.y - 0.5;

        while (x >= y)
        {
            SetPixel(renderer, {(int)(cx + x), (int)(cy + y)}, rgb);
            SetPixel(renderer, {(int)(cx + y), (int)(cy + x)}, rgb);

            if (x != 0)
            {
                SetPixel(renderer, {(int)(cx - x), (int)(cy + y)}, rgb);
                SetPixel(renderer, {(int)(cx + y), (int)(cy - x)}, rgb);
            }

            if (y != 0)
            {
                SetPixel(renderer, {(int)(cx + x), (int)(cy - y)}, rgb);
                SetPixel(renderer, {(int)(cx - y), (int)(cy + x)}, rgb);
            }

            if (x != 0 && y != 0)
            {
                SetPixel(renderer, {(int)(cx - x), (int)(cy - y)}, rgb);
                SetPixel(renderer, {(int)(cx - y), (int)(cy - x)}, rgb);
            }

            error += y;
            ++y;
            error += y;

            if (error >= 0)
            {
                --x;
                error -= x;
                error -= x;
            }
        }
    }

    void FillCircle(SDL_Renderer *renderer, const olc::vi2d &point, int radius, const std::array<uint8_t, 4> &rgb)
    {
        for (double dy = 1; dy <= radius; dy += 1.0)
        {
            double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
            SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], rgb[3]);
            SDL_RenderDrawLine(renderer, point.x - dx, point.y + dy - radius, point.x + dx, point.y + dy - radius);
            SDL_RenderDrawLine(renderer, point.x - dx, point.y - dy + radius, point.x + dx, point.y - dy + radius);
        }
    }
}

namespace sgraphics
{
    SdlRenderer::SdlRenderer(IWindow::Ptr window)
    {
        auto pointer = dynamic_cast<SdlWindow *>(window.get());
        renderer_ = SDL_CreateRenderer(pointer->window_, -1, 0); 
    }

    SdlRenderer::~SdlRenderer() 
    {
        SDL_DestroyRenderer(renderer_);
    }

    void SdlRenderer::ClearScreen(const RgbType &rgb)
    {
        SDL_SetRenderDrawColor(renderer_, rgb[0], rgb[1], rgb[2], rgb[3]);
        SDL_RenderClear(renderer_);
    }

    void SdlRenderer::RenderClear()
    {
        SDL_RenderClear(renderer_);
    }

    void SdlRenderer::RenderPresent()
    {
        SDL_RenderPresent(renderer_);
    }

    void SdlRenderer::DrawRect(const FRectType &rect, const RgbType &rbg, bool fill)
    {
        auto sdlRect = convertion::convert(rect);

        SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer_, rbg[0], rbg[1], rbg[2], rbg[3]);

        fill ? SDL_RenderFillRectF(renderer_, &sdlRect)
             : SDL_RenderDrawRectF(renderer_, &sdlRect);
    }

    void SdlRenderer::DrawRect(const IntRectType &rect, const RgbType &rbg, bool fill)
    {
        auto sdlRect = convertion::convert(rect);

        SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer_, rbg[0], rbg[1], rbg[2], rbg[3]);

        fill ? SDL_RenderFillRect(renderer_, &sdlRect)
             : SDL_RenderDrawRect(renderer_, &sdlRect);
    }

    void SdlRenderer::DrawLine(const olc::vf2d &point1, const olc::vf2d &point2, const RgbType &rbg)
    {
        auto sdlPoint1 = convertion::convert(point1);
        auto sdlPoint2 = convertion::convert(point2);

        SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer_, rbg[0], rbg[1], rbg[2], rbg[3]);
        SDL_RenderDrawLine(renderer_, sdlPoint1.x, sdlPoint1.y, sdlPoint2.x, sdlPoint2.y);
    }

    void SdlRenderer::DrawCircle(const olc::vi2d &point, std::int32_t radius, const RgbType &rbg, bool fill)
    {
        SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

        fill ? ::FillCircle(renderer_, point, radius, rbg)
             : ::DrawCircle(renderer_, point, radius, rbg);
    }

    ITexture::Ptr SdlRenderer::CreateTexture(IImage::Ptr image)
    {
        if (!image)
            return nullptr;

        auto sdlImageImpl = dynamic_cast<SdlImageImpl *>(image.get());
        return ITexture::Ptr(new SdlTextureImpl(renderer_, sdlImageImpl->serface_));
    }

    bool SdlRenderer::RenderCopy(ITexture::Ptr texture, const FRectType &src, const FRectType &dest)
    {
        if (!texture)
            return false;

        auto sdlTextureImpl = dynamic_cast<SdlTextureImpl *>(texture.get());

        SDL_FRect destSdl = convertion::convert(dest);
        SDL_FRect srcFSdl = convertion::convert(src);
        SDL_Rect srcSdl{(int)srcFSdl.x, (int)srcFSdl.y, (int)srcFSdl.w, (int)srcFSdl.h};
        return !SDL_RenderCopyF(renderer_, sdlTextureImpl->texture_, &srcSdl, &destSdl);
    }

    bool SdlRenderer::RenderCopy(ITexture::Ptr texture, const IntRectType &src, const IntRectType &dest)
    {
        if (!texture)
            return false;

        auto sdlTextureImpl = dynamic_cast<SdlTextureImpl *>(texture.get());

        SDL_Rect destSdl = convertion::convert(dest);
        SDL_Rect srcFSdl = convertion::convert(src);
        SDL_Rect srcSdl{(int)srcFSdl.x, (int)srcFSdl.y, (int)srcFSdl.w, (int)srcFSdl.h};
        return !SDL_RenderCopy(renderer_, sdlTextureImpl->texture_, &srcSdl, &destSdl);
    }
}
