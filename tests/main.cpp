#include <iostream>
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
    class TestGameImpl final : public sg::BaseGame
    {
    public:
        TestGameImpl(const std::string &title)
            : sg::BaseGame(title),
              renderer_(sg::GetEngine().GetRenderer()),
              eventer_(sg::GetEngine().GetEventer()),
              collision_(sg::ICollision::Create(sg::CollisionType::Dynamic))
        {
            if (eventer_)
            {
                eventer_->AddEventHandler(*this, &TestGameImpl::EventHandler);
            }

            rectsPtr_.push_back(new sg::FRectType({{200, 400}, {400, 50}}));
            // rectsPtr_.push_back(new FRectType());
            // rectsPtr_.push_back(new FRectType());
        }

        ~TestGameImpl() override
        {
            for (auto rect : rectsPtr_)
            {
                delete rect;
            }
        }

        void OnUpdate(const Duration &duration) override
        {
            renderer_->ClearScreen({255, 255, 255, 255});
            auto timeMs = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

            olc::vf2d mousePos{(float)mousePosition_.first, (float)mousePosition_.second};
            olc::vf2d centr {dynamicRect_.pos.x + dynamicRect_.size.x / 2, dynamicRect_.pos.y + dynamicRect_.size.y / 2}; 
            olc::vf2d ray = mousePos - centr;

            if (MouseDown_)
            {
                dynamicRect_.vel += ray.norm() * timeMs / 3000;
            }

            // sg::IntRectType staticRect({{200, 400}, {400, 50}});
            // bool fill = PointVsRect(staticRect) ? true : false;

            renderer_->DrawLine(mousePos, centr, {255, 0, 0, 255});
            renderer_->DrawRect(dynamicRect_, {255, 0, 0, 255}, false);

            for (auto rect : rectsPtr_)
            {
                renderer_->DrawRect(*rect, {255, 0, 0, 255}, false);
            }

            if (collision_->Calculate(dynamicRect_, rectsPtr_, timeMs))
            {
                // dynamicRect_.vel = {0, 0};
            }

            dynamicRect_.pos += dynamicRect_.vel * timeMs;
        }

        void OnQuit() override {}

        void EventHandler(sg::IEvent::Ptr event)
        {
            if (!event)
                return;

            mousePosition_ = event->GetMousePosition();

            switch (event->GetType())
            {
            case sg::EventType::Quit:
                quit_ = true;
                break;
            case sg::EventType::MouseButtonDown:
            {
                MouseDown_ = true;
                break;
            }
            case sg::EventType::MouseButtonUp:
            {
                MouseDown_ = false;
                break;
            }

            default:
                break;
            }
        }

    private:
        bool PointVsRect(const sg::IntRectType &rect)
        {
            return (mousePosition_.first >= rect.pos.x &&
                    mousePosition_.second >= rect.pos.y &&
                    mousePosition_.first <= rect.pos.x + rect.size.x &&
                    mousePosition_.second <= rect.pos.y + rect.size.y);
        }

    private:
        sg::IRenderer::Ptr renderer_;
        sg::IEventer::Ptr eventer_;
        sg::MousePosType mousePosition_;
        sg::FRectType dynamicRect_{{78, 180}, {50, 50}};
        bool MouseDown_{false};
        sg::ICollision::RectsType rectsPtr_;
        sg::ICollision::Ptr collision_;
    };
}

int main(int argc, char *argv[])
{
    try
    {
        TestGameImpl game("TestGameImpl");
        game.Run();
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    return 0;
}
