#pragma once

#include "../IFont.hpp"

#include "third_party/sdl_font_cache/SDL_FontCache.h"

#include <filesystem>
#include <SDL2/SDL.h>

namespace sg
{
    class SdlFont final : public IFont
    {
    private:
        FC_Font *m_font;
        SDL_Renderer *m_renderer;

    public:
        explicit SdlFont(SDL_Renderer *renderer, const std::filesystem::path filename);
        ~SdlFont() override;
        bool PrintText(const std::string &text) override;
    };

}
