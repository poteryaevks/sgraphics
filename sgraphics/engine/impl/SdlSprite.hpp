#pragma once

#include <array>
#include <chrono>
#include <memory>

#include <sgraphics/engine/IImage.hpp>
#include <sgraphics/engine/ITexture.hpp>

#include <sgraphics/convertion/convertion.h>
#include <sgraphics/geometry/olc.h>
#include <sgraphics/geometry/types.hpp>

#include "../ISprite.hpp"

namespace sg
{
    struct SdlImageImpl;
    struct SdlTextureImpl;

    class SdlSprite final : public ISprite
    {
    public:
        SdlSprite(const std::filesystem::path &path, const RgbType &rbg);
        ~SdlSprite() override;

        void RenderCopy(const FloatRectType &src, const FloatRectType &dest) override;
        void RenderCopy(const IntRectType &src, const IntRectType &dest) override;

    private:
        IImage::Ptr img_;
        ITexture::Ptr texture_;
    };
}
