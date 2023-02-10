#include <iostream>
#include <string>

#include "sgraphics/geometry/types.hpp"
#include "sgraphics/geometry/olc.h"
#include "sgraphics/engine/IRenderer.hpp"
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
              eventer_(sg::GetEngine().GetEventer())
        {
            if (eventer_)
            {
                eventer_->AddEventHandler(*this, &TestGameImpl::EventHandler);
            }
        }

        ~TestGameImpl() = default;

        void OnUpdate(const Duration &duration) override
        {
            renderer_->ClearScreen({255, 255, 255, 255});

            renderer_->DrawRect(sg::IntRectType({{0, 0}, {20, 20}}),
                                {255, 0, 0, 100}, true);

            renderer_->DrawCircle({500, 500}, 100, {255, 0, 0, 100}, true);
        }

        void OnQuit() override {}

        void EventHandler(sg::IEvent::Ptr event)
        {
            if (!event)
                return;

            switch (event->GetType())
            {
            case sg::EventType::Quit:
                quit_ = true;
                break;

            default:
                break;
            }
        }

    private:
        sg::IRenderer::Ptr renderer_;
        sg::IEventer::Ptr eventer_;
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
