#pragma once

#include <chrono>
#include <string>

namespace sg
{
    class BaseGame
    {
    public:
        using Duration = std::chrono::nanoseconds;
        using Clock = std::chrono::system_clock;
        BaseGame(const std::string &title, int width = 800, int hight = 640);
        virtual ~BaseGame();
        void Run();
        virtual void OnCreate() = 0;
        virtual void OnUpdate(const Duration &) = 0;
        virtual void OnQuit() = 0;

    protected:
        bool quit_{false};
    };
}
