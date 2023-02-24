#pragma once

#include <string>
#include <thread>
#include <chrono>

#include "sgraphics/geometry/types.hpp"
#include "sgraphics/geometry/olc.h"
#include "sgraphics/engine/IRenderer.hpp"
#include "sgraphics/engine/IFont.hpp"
#include "sgraphics/engine/Engine.hpp"
#include "sgraphics/engine/BaseGame.hpp"

#include <boost/format.hpp>

namespace
{
    using namespace std::chrono_literals;
    const olc::vi2d TILE{50, 50};
    const olc::vi2d MAP_SIZE{16, 16};
    constexpr float MaxDistance{2000};

    class DdaAlgorithm final : public sg::BaseGame
    {
    public:
        using PairType = std::pair<sg::IntRectType, sg::RgbType>;

        DdaAlgorithm(const std::string &title, int width = 1024, int hight = 840)
            : sg::BaseGame(title, width, hight),
              renderer_(sg::GetEngine().GetRenderer()),
              window_(sg::GetEngine().GetWindow()),
              eventer_(sg::GetEngine().GetEventer()),
              m_font(sg::GetEngine().CreateFont())
        {
            for (int i = 0; i < MAP_SIZE.y; ++i)
            {
                for (int j = 0; j < MAP_SIZE.x; ++j)
                {
                    rects_.push_back({sg::IntRectType({{i * TILE.x, j * TILE.y}, TILE}), sg::TRANSPER_DARK_BLUE});
                }
            }
        }

        void OnCreate() override
        {
            renderer_->ClearScreen(sg::WHITE);
            for (int y = 0; y < MAP_SIZE.y; ++y)
            {
                for (int x = 0; x < MAP_SIZE.x; ++x)
                {
                    std::size_t i = x * MAP_SIZE.x + y;
                    renderer_->DrawRect(rects_[i].first, sg::TRANSPER_DARK_BLUE, false);
                    renderer_->RenderPresent();
                    std::this_thread::sleep_for(5ms);
                }
            }
        }

        ~DdaAlgorithm() override = default;

        void OnUpdate(const Duration &duration) override
        {
            quit_ = eventer_->Quit();

            auto endPoint = eventer_->MousePosition();
            renderer_->ClearScreen(sg::WHITE);
            renderer_->DrawCircle(endPoint, 10, sg::RED, true);

            if (eventer_->SHold()) { startPoint_.y += 1; }
            if (eventer_->WHold()) { startPoint_.y -= 1; }
            if (eventer_->AHold()) { startPoint_.x -= 1; }
            if (eventer_->DHold()) { startPoint_.x += 1; }

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
            }

            renderer_->DrawCircle(startPoint_, 10, sg::GREEN, true);
            renderer_->DrawLine(startPoint_, eventer_->MousePosition(), sg::RED);

            // draw point of a first intersection
            if (eventer_->RightMouseHold())
            {
                DoRayCasting(endPoint);
            }

            auto txt = boost::format("FPS: %ld {%d, %d} {%d, %d}") //
                       % (std::nano::den / duration.count())       //
                       % startPoint_.x                             //
                       % startPoint_.y                             //
                       % eventer_->MousePosition().x               //
                       % eventer_->MousePosition().y               //
                ;

            m_font->PrintText(txt.str());
        }

        void DoRayCasting(olc::vf2d endPoint)
        {
            auto direction = (endPoint - startPoint_).norm();

            olc::vf2d scaleFactor = {std::sqrt(1 + (direction.y / direction.x) * (direction.y / direction.x)),
                                     std::sqrt(1 + (direction.x / direction.y) * (direction.x / direction.y))};

            olc::vi2d tile{int(startPoint_.x / TILE.x), int(startPoint_.y / TILE.y)};
            bool found{false};
            float distance{};
            olc::vf2d length;
            olc::vi2d delta;
            olc::vi2d tileStep;
            olc::vi2d distanceStep{TILE};

            if (direction.x > 0)
            {
                delta.x = TILE.x - (int)startPoint_.x % TILE.x;
                tileStep.x = 1;
            }
            else
            {
                delta.x = (int)startPoint_.x % TILE.x;
                tileStep.x = -1;
            }

            if (direction.y > 0)
            {
                delta.y = TILE.y - (int)startPoint_.y % TILE.y;
                tileStep.y = 1;
            }
            else
            {
                delta.y = (int)startPoint_.y % TILE.y;
                tileStep.y = -1;
            }

            while (distance < MaxDistance && !found)
            {
                length.x = scaleFactor.x * delta.x;
                length.y = scaleFactor.y * delta.y;

                if (length.x < length.y)
                {
                    distance = length.x;
                    tile.x += tileStep.x;
                    delta.x += distanceStep.x;
                }
                else
                {
                    distance = length.y;
                    tile.y += tileStep.y;
                    delta.y += distanceStep.y;
                }

                std::size_t i = tile.x * MAP_SIZE.y + tile.y;
                if (i < rects_.size())
                {
                    if (rects_[i].second == sg::DARK_BLUE)
                    {
                        olc::vf2d point{direction * distance};
                        point += startPoint_;

                        renderer_->DrawRect(rects_[i].first, sg::RED, true);
                        renderer_->DrawCircle(point, 10, sg::YELLOW, true);
                        found = true;
                    }
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

        int ToDegrees(olc::vf2d vec)
        {
            return std::atan2(vec.y, vec.x) * 180 / M_PI;
        }

    private:
        sg::IRenderer::Ptr renderer_;
        sg::IWindow::Ptr window_;
        sg::IEventer::Ptr eventer_;
        sg::IFont::Ptr m_font;
        olc::vf2d startPoint_{};
        std::vector<PairType> rects_;
    };
}
