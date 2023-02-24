#pragma once

#include "../IEventer.hpp"
#include "../IEvent.hpp"
#include "SdlEvent.hpp"

#include "sgraphics/geometry/types.hpp"

#include <SDL2/SDL.h>

namespace sgraphics
{
    class SdlEventer final : public IEventer
    {
    private:
        SDL_Event event_;
        SdlEvent::Ptr sdlEvent_;

    public:
        SdlEventer();
        ~SdlEventer() override;
        bool OnUpdate() override;
        bool LeftMouseDown() const override;
        bool LeftMouseUp() const override;
        bool RightMouseDown() const override;
        bool RightMouseUp() const override;
        bool LeftMouseHold() const override;
        bool RightMouseHold() const override;
        bool SUp() const override;
        bool SDown() const override;
        bool AUp() const override;
        bool ADown() const override;
        bool WUp() const override;
        bool WDown() const override;
        bool DUp() const override;
        bool DDown() const override;
        bool DHold() const override;
        bool AHold() const override;
        bool SHold() const override;
        bool WHold() const override;
        bool Quit() const override;
        MousePosType MousePosition() const override;
    };
}
