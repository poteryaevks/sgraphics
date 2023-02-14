#include "BaseGame.hpp"
#include "Engine.hpp"
#include "IEventer.hpp"

#include <sgraphics/geometry/olc.h>
#include <sgraphics/geometry/types.hpp>

#include <string>
#include <iostream>
#include <stdexcept>
#include <thread>

namespace
{
    using namespace std::chrono_literals;
}

namespace sg
{
    BaseGame::BaseGame(const std::string &title, int width, int hight)
    {
        if (!GetEngine().Init(title, width, hight))
        {
            throw std::runtime_error("Unable to init engine");
        }
    }

    BaseGame::~BaseGame() = default;
    void BaseGame::Run()
    {
        auto start{Clock::now()};
        auto eventer = GetEngine().GetEventer();
        auto renderer = GetEngine().GetRenderer();

        while (!quit_)
        {
            start = Clock::now();
            renderer->RenderClear();
            eventer->OnUpdate();
            std::this_thread::sleep_for(1ms);
            this->OnUpdate(Clock::now() - start);
            renderer->RenderPresent();
        }

        this->OnQuit();
    }
}
