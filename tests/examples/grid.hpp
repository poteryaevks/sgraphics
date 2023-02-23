#pragma once

#include <string>
#include <chrono>

#include "sgraphics/geometry/types.hpp"
#include "sgraphics/geometry/olc.h"
#include "sgraphics/engine/IRenderer.hpp"
#include "sgraphics/engine/Engine.hpp"
#include "sgraphics/engine/BaseGame.hpp"

namespace
{
    class Grid final : public sg::BaseGame
    {
    public:
        using PairType = std::pair<sg::IntRectType, sg::RgbType>;

        Grid(const std::string &title, int width = 800, int hight = 640)
            : sg::BaseGame(title, width, hight),
              renderer_(sg::GetEngine().GetRenderer()),
              window_(sg::GetEngine().GetWindow()),
              eventer_(sg::GetEngine().GetEventer())
        {
            for (int i = 0; i < width / 20; ++i)
            {
                for (int j = 0; j < hight / 20; ++j)
                {
                    rects_.push_back({sg::IntRectType({{i * 20, j * 20}, {20, 20}}), sg::TRANSPER_DARK_BLUE});
                }
            }
        }

        ~Grid() override = default;

        void OnUpdate(const Duration &duration) override
        {
            quit_ = eventer_->Quit();

            renderer_->ClearScreen({255, 255, 255, 255});

            for (auto &[rect, color] : rects_)
            {
                if (PointVsRect(rect) && eventer_->LeftMouseHold())
                {
                    color = sg::DARK_BLUE;
                    renderer_->DrawRect(rect, color, true);
                }
                else
                {
                    bool fill = (color == sg::DARK_BLUE) ? true : false;
                    renderer_->DrawRect(rect, color, fill);
                }

                if (PointVsRect(rect) && eventer_->RightMouseHold())
                {
                    color = sg::TRANSPER_DARK_BLUE;
                    renderer_->DrawRect(rect, color, false);
                }
            }
        }

        void OnQuit() override {}

        bool PointVsRect(const sg::IntRectType &rect)
        {
            return (eventer_->MousePosition().x >= rect.pos.x &&
                    eventer_->MousePosition().y >= rect.pos.y &&
                    eventer_->MousePosition().x <= rect.pos.x + rect.size.x &&
                    eventer_->MousePosition().y <= rect.pos.y + rect.size.y);
        }

    private:
        sg::IRenderer::Ptr renderer_;
        sg::IWindow::Ptr window_;
        sg::IEventer::Ptr eventer_;
        // sg::MousePosType mousePosition_;
        // bool leftMouseDown_{false};
        // bool rightMouseDown_{false};
        std::vector<PairType> rects_;
    };
}
