#include "SdlEventer.hpp"

namespace sgraphics
{
    SdlEventer::SdlEventer()
        : sdlEvent_(IEvent::Ptr(new SdlEvent(event_)))
    {
    }

    SdlEventer::~SdlEventer() = default;

    bool SdlEventer::OnUpdate()
    {
        SDL_PollEvent(&event_);
        sdlEvent_->Update();
        invoker_(sdlEvent_);
        return true;
    };

    bool SdlEventer::LeftMouseDown() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetMouseEvent() == MouseEvent::LeftDown;
    }

    bool SdlEventer::LeftMouseUp() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetMouseEvent() == MouseEvent::LeftUp;
    }

    bool SdlEventer::RightMouseDown() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetMouseEvent() == MouseEvent::RightDown;
    }

    bool SdlEventer::RightMouseUp() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetMouseEvent() == MouseEvent::RightUp;
    }

    bool SdlEventer::SUp() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::SUp;
    }

    bool SdlEventer::SDown() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::SDown;
    }

    bool SdlEventer::AUp() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::AUp;
    }

    bool SdlEventer::ADown() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::ADown;
    }

    bool SdlEventer::WUp() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::WUp;
    }

    bool SdlEventer::WDown() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::WDown;
    }

    bool SdlEventer::DUp() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::DUp;
    }

    bool SdlEventer::DDown() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::DDown;
    }

    MousePosType SdlEventer::MousePosition() const
    {
        if (!sdlEvent_)
        {
            return {};
        }

        return sdlEvent_->GetMousePosition();
    }

    bool SdlEventer::LeftMouseHold() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetMouseEvent() == MouseEvent::LeftHold;
    }

    bool SdlEventer::RightMouseHold() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetMouseEvent() == MouseEvent::RightHold;
    }

    bool SdlEventer::DHold() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::DHold;
    }

    bool SdlEventer::AHold() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::AHold;
    }

    bool SdlEventer::SHold() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::SHold;
    }

    bool SdlEventer::WHold() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetKeyboardEvent() == KeyboardEvent::WHold;
    }

    bool SdlEventer::Quit() const
    {
        if (!sdlEvent_)
            return false;

        return sdlEvent_->GetCommandEvent() == CommandEvent::Quit;
    }
}
