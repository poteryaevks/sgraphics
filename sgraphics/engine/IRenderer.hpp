#pragma once

#include <sgraphics/geometry/types.hpp>
#include <sgraphics/engine/IImage.hpp>
#include <sgraphics/engine/ITexture.hpp>

#include <boost/noncopyable.hpp>

#include <memory>

namespace sgraphics
{
    class IRenderer : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<IRenderer>;
        virtual void ClearScreen(const RgbType &rgb) = 0;
        virtual void RenderClear() = 0;
        virtual void RenderPresent() = 0;
        virtual void DrawRect(const FRectType &rect, const RgbType &rbg = {0, 0, 0, 255}, bool fill = false) = 0;
        virtual void DrawRect(const IntRectType &rect, const RgbType &rbg, bool fill = false) = 0;
        virtual void DrawLine(const olc::vf2d &point1, const olc::vf2d &point2, const RgbType &rbg = {0, 0, 0, 255}) = 0;
        virtual void DrawCircle(const olc::vi2d &point, std::int32_t radius, const RgbType &rbg = {0, 0, 0, 255}, bool fill = false) = 0;
        virtual ITexture::Ptr CreateTexture(IImage::Ptr) = 0;
        virtual bool RenderCopy(ITexture::Ptr texture, const FRectType &src, const FRectType &dest) = 0;
        virtual bool RenderCopy(ITexture::Ptr texture, const IntRectType &src, const IntRectType &dest) = 0;
        virtual ~IRenderer() = default;
    };
}
