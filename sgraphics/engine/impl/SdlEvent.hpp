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
        EventType type{EventType::Unable};

    public:
        SdlEvent(const SDL_Event &event)
            : event_(event)
        {
            SDL_GetMouseState(&(mousePos_.first), &(mousePos_.second));

            switch (event_.type)
            {
            case SDL_MOUSEBUTTONDOWN:
            {
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    type = EventType::MouseButtonDown;
                    break;
                default:
                    break;
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    type = EventType::MouseButtonUp;
                    break;
                default:
                    break;
                }
                break;
            }
            case SDL_QUIT:
            {
                type = EventType::Quit;
                break;
            }   
            default:
                break;
            }
        }

        ~SdlEvent() = default;

        EventType GetType() const override
        {
            return type;
        }

        MousePosType GetMousePosition() const override
        {
            return mousePos_;
        }
    };
}
