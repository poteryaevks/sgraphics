#pragma once

#include "../IEvent.hpp"

#include "sgraphics/geometry/types.hpp"
#include <SDL2/SDL.h>

namespace sg
{
    class SdlEvent final : public IEvent
    {
    private:
        const SDL_Event &event_;
        MousePosType mousePos_;
        KeyboardEvent keyboardEventType_{KeyboardEvent::None};
        MouseEvent mouseEventType_{MouseEvent::None};
        CommandEvent commandEventType_{CommandEvent::None};

        bool mouseLeftHold_{false};
        bool mouseRightHold_{false};
        bool sHold_{false};
        bool wHold_{false};
        bool dHold_{false};
        bool aHold_{false};

    public:
        SdlEvent(const SDL_Event &event) : event_(event) {}
        ~SdlEvent() override = default;

        void Update() override
        {
            keyboardEventType_ = KeyboardEvent::None;
            mouseEventType_ = MouseEvent::None;
            commandEventType_ = CommandEvent::None;

            SDL_GetMouseState(&(mousePos_.x), &(mousePos_.y));

            switch (event_.type)
            {
            case SDL_KEYDOWN:
            {
                switch (event_.key.keysym.sym)
                {
                case SDLK_a:
                    keyboardEventType_ = KeyboardEvent::ADown;
                    break;
                case SDLK_s:
                    keyboardEventType_ = KeyboardEvent::SDown;
                    break;
                case SDLK_w:
                    keyboardEventType_ = KeyboardEvent::WDown;
                    break;
                case SDLK_d:
                    keyboardEventType_ = KeyboardEvent::DDown;
                    break;
                default:
                    break;
                }
                
                break;
            }
            case SDL_KEYUP:
            {
                switch (event_.key.keysym.sym)
                {
                case SDLK_a:
                    keyboardEventType_ = KeyboardEvent::AUp;
                    aHold_ = false;
                    break;
                case SDLK_s:
                    keyboardEventType_ = KeyboardEvent::AUp;
                    sHold_ = false;
                    break;
                case SDLK_w:
                    keyboardEventType_ = KeyboardEvent::WUp;
                    wHold_ = false;
                    break;
                case SDLK_d:
                    keyboardEventType_ = KeyboardEvent::DUp;
                    dHold_ = false;
                    break;
                default:
                    break;
                }

                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                switch (event_.button.button)
                {
                case SDL_BUTTON_LEFT:
                {
                    mouseEventType_ = MouseEvent::LeftDown;
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    mouseEventType_ = MouseEvent::RightDown;
                    break;
                }
                default:
                    break;
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                switch (event_.button.button)
                {
                case SDL_BUTTON_LEFT:

                    mouseEventType_ = MouseEvent::LeftUp;
                    mouseLeftHold_ = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    mouseEventType_ = MouseEvent::RightUp;
                    mouseRightHold_ = false;
                    break;
                default:
                    break;
                }
                break;
            }
            case SDL_QUIT:
            {
                commandEventType_ = CommandEvent::Quit;
                break;
            }
            default:
                break;
            }

            CheckSHold();
            CheckWHold();
            CheckDHold();
            CheckAHold();
            CheckHoldLeftMouse();
            CheckHoldRightMouse();
        }

        KeyboardEvent GetKeyboardEvent() const override
        {
            return keyboardEventType_;
        }

        const MousePosType &GetMousePosition() const override
        {
            return mousePos_;
        }

        MouseEvent GetMouseEvent() const override
        {
            return mouseEventType_;
        }

        CommandEvent GetCommandEvent() const override
        {
            return commandEventType_;
        }

    private:
        void CheckHoldLeftMouse()
        {
            if (mouseLeftHold_)
            {
                mouseEventType_ = MouseEvent::LeftHold;
            }
            else
            {
                mouseLeftHold_ = (mouseEventType_ == MouseEvent::LeftDown);
            }
        }

        void CheckHoldRightMouse()
        {
            if (mouseRightHold_)
            {
                mouseEventType_ = MouseEvent::RightHold;
            }
            else
            {
                mouseRightHold_ = (mouseEventType_ == MouseEvent::RightDown);
            }
        }

        void CheckSHold()
        {
            if (sHold_)
            {
                keyboardEventType_ = KeyboardEvent::SHold;
            }
            else
            {
                sHold_ = (keyboardEventType_ == KeyboardEvent::SDown);
            }
        }

        void CheckAHold()
        {
            if (aHold_)
            {
                keyboardEventType_ = KeyboardEvent::AHold;
            }
            else
            {
                aHold_ = (keyboardEventType_ == KeyboardEvent::ADown);
            }
        }

        void CheckDHold()
        {
            if (dHold_)
            {
                keyboardEventType_ = KeyboardEvent::DHold;
            }
            else
            {
                dHold_ = (keyboardEventType_ == KeyboardEvent::DDown);
            }
        }

        void CheckWHold()
        {
            if (wHold_)
            {
                keyboardEventType_ = KeyboardEvent::WHold;
            }
            else
            {
                wHold_ = (keyboardEventType_ == KeyboardEvent::WDown);
            }
        }
    };
}
