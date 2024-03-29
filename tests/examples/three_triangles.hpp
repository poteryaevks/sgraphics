#pragma once

#include <string>
#include <chrono>

#include "sgraphics/geometry/types.hpp"
#include "sgraphics/geometry/olc.h"
#include "sgraphics/engine/IRenderer.hpp"
#include "sgraphics/engine/ICollision.hpp"
#include "sgraphics/engine/Engine.hpp"
#include "sgraphics/engine/BaseGame.hpp"

namespace
{
    class TreeTrianglesExample final : public sgraphics::BaseGame
    {
    public:
        TreeTrianglesExample(const std::string &title)
            : sgraphics::BaseGame(title),
              renderer_(sgraphics::GetEngine().GetRenderer()),
              eventer_(sgraphics::GetEngine().GetEventer()),
              collision_(sgraphics::ICollision::Create(sgraphics::CollisionType::Dynamic2))
        {
            rectsPtr_.push_back(new sgraphics::FRectType({{200, 400}, {400, 50}}));
            rectsPtr_.push_back(new sgraphics::FRectType({{400, 10}, {50, 380}}));
            // rectsPtr_.push_back(new sg::FRectType());
        }

        ~TreeTrianglesExample() override
        {
            for (auto rect : rectsPtr_)
            {
                delete rect;
            }
        }

        void OnCreate() override {}

        void OnUpdate(const Duration &duration) override
        {
            quit_ = eventer_->Quit();
            renderer_->ClearScreen({255, 255, 255, 255});
            auto timeMs = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

            olc::vf2d centr{dynamicRect_.pos.x + dynamicRect_.size.x / 2, dynamicRect_.pos.y + dynamicRect_.size.y / 2};
            olc::vf2d ray = eventer_->MousePosition() - centr;

            if (eventer_->LeftMouseHold())
            {
                dynamicRect_.vel +=  ray.norm() * timeMs / 3000;
            }

            // sg::IntRectType staticRect({{200, 400}, {400, 50}});
            // bool fill = PointVsRect(staticRect) ? true : false;

            renderer_->DrawLine(eventer_->MousePosition(), centr, {255, 0, 0, 255});
            renderer_->DrawRect(dynamicRect_, {255, 0, 0, 255}, false);

            for (auto rect : rectsPtr_)
            {
                renderer_->DrawRect(*rect, {255, 0, 0, 255});
            }

            if (collision_->Calculate(dynamicRect_, rectsPtr_, timeMs))
            {
                for (const auto &rect : dynamicRect_.contact)
                {
                    if (rect)
                    {
                        renderer_->DrawRect(*rect, {255, 160, 0, 255}, true);
                    }
                }
            }

            dynamicRect_.pos += dynamicRect_.vel * timeMs;
        }

        void OnQuit() override {}

    private:
        bool PointVsRect(const sgraphics::IntRectType &rect)
        {
            return (eventer_->MousePosition().x >= rect.pos.x &&
                    eventer_->MousePosition().y >= rect.pos.y &&
                    eventer_->MousePosition().x <= rect.pos.x + rect.size.x &&
                    eventer_->MousePosition().y <= rect.pos.y + rect.size.y);
        }

    private:
        sgraphics::IRenderer::Ptr renderer_;
        sgraphics::IEventer::Ptr eventer_;
        sgraphics::FRectType dynamicRect_{{78, 180}, {50, 50}};
        sgraphics::ICollision::RectsType rectsPtr_;
        sgraphics::ICollision::Ptr collision_;
    };
}
