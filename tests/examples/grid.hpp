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
    class Grid final : public sgraphics::BaseGame
    {
    public:
        using PairType = std::pair<sgraphics::IntRectType, sgraphics::RgbType>;

        Grid(const std::string &title, int width = 800, int hight = 640)
            : sgraphics::BaseGame(title, width, hight),
              renderer_(sgraphics::GetEngine().GetRenderer()),
              window_(sgraphics::GetEngine().GetWindow()),
              eventer_(sgraphics::GetEngine().GetEventer())
        {
            for (int i = 0; i < width / 20; ++i)
            {
                for (int j = 0; j < hight / 20; ++j)
                {
                    rects_.push_back({sgraphics::IntRectType({{i * 20, j * 20}, {20, 20}}), sgraphics::TRANSPER_DARK_BLUE});
                }
            }
        }

        ~Grid() override = default;

        void OnCreate() override {}

        void OnUpdate(const Duration &duration) override
        {
            quit_ = eventer_->Quit();

            renderer_->ClearScreen({255, 255, 255, 255});

            for (auto &[rect, color] : rects_)
            {
                if (PointVsRect(rect) && eventer_->LeftMouseHold())
                {
                    color = sgraphics::DARK_BLUE;
                    renderer_->DrawRect(rect, color, true);
                }
                else
                {
                    bool fill = (color == sgraphics::DARK_BLUE) ? true : false;
                    renderer_->DrawRect(rect, color, fill);
                }

                if (PointVsRect(rect) && eventer_->RightMouseHold())
                {
                    color = sgraphics::TRANSPER_DARK_BLUE;
                    renderer_->DrawRect(rect, color, false);
                }
            }
        }

        void OnQuit() override {}

        bool PointVsRect(const sgraphics::IntRectType &rect)
        {
            return (eventer_->MousePosition().x >= rect.pos.x &&
                    eventer_->MousePosition().y >= rect.pos.y &&
                    eventer_->MousePosition().x <= rect.pos.x + rect.size.x &&
                    eventer_->MousePosition().y <= rect.pos.y + rect.size.y);
        }

    private:
        sgraphics::IRenderer::Ptr renderer_;
        sgraphics::IWindow::Ptr window_;
        sgraphics::IEventer::Ptr eventer_;
        std::vector<PairType> rects_;
    };
}
