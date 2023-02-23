#include "SdlFont.hpp"

#include <stdexcept>

namespace sg
{
    SdlFont::SdlFont(SDL_Renderer *renderer, const std::filesystem::path filename)
        : IFont(),
          m_renderer(renderer)
    {
        m_font = FC_CreateFont();
        if (!m_font || !m_renderer)
        {
            throw std::runtime_error("Invalid font");
        }

        if (!std::filesystem::exists(filename))
        {
            throw std::runtime_error("File doesn't exist");
        }

        FC_LoadFont(m_font, m_renderer, filename.string().data(), 20, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
    }

    SdlFont::~SdlFont()
    {
        FC_FreeFont(m_font);
    }

    bool SdlFont::PrintText(const std::string &text)
    {
        if(!m_renderer || !m_font)
        {
            return false;
        }

        FC_Draw(m_font, m_renderer, 0, 0, "%s", text.data());
        return true;
    }
}
