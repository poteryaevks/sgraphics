#pragma once

#include "../IEventer.hpp"
#include "../IEvent.hpp"

#include <SDL2/SDL.h>

namespace sg
{
    class SdlEventer final : public IEventer
    {
    private:
        SDL_Event event_;

    public:
        SdlEventer();
        ~SdlEventer() override;
        bool OnUpdate() override;
    };
}
