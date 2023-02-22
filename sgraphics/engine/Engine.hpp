#pragma once

#include <alm/misc/singleton.h>

#include <sgraphics/geometry/types.hpp>
#include <sgraphics/engine/IRenderer.hpp>
#include <sgraphics/engine/IEventer.hpp>
#include <sgraphics/engine/IWindow.hpp>
#include <sgraphics/engine/ISprite.hpp>

#include <filesystem>

namespace sg
{
    class Engine : public alm::misc::Singleton<Engine>
    {
        friend class alm::misc::Singleton<Engine>;

    public:
        bool Init(const std::string &title, int width, int hight);
        IWindow::Ptr GetWindow();
        IRenderer::Ptr GetRenderer();
        IEventer::Ptr GetEventer();
        ISprite::Ptr CreateSprite(const std::filesystem::path &path, const RgbType &rgb);
        ISprite::Ptr CreateText(const std::filesystem::path &path, const RgbType &rgb);

    private:
        Engine();
        ~Engine();

        bool inited_{false};
        IWindow::Ptr window_;
        IRenderer::Ptr renderer_;
        IEventer::Ptr eventer_;
    };

    inline Engine &GetEngine() { return Engine::instance(); }
}
