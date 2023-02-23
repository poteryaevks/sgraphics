#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <optional>

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

    class DdaAlgorithm final : public sg::BaseGame
    {
    public:
        using PairType = std::pair<sg::IntRectType, sg::RgbType>;

        DdaAlgorithm(const std::string &title, int width = 800, int hight = 650)
            : sg::BaseGame(title, width, hight),
              renderer_(sg::GetEngine().GetRenderer()),
              window_(sg::GetEngine().GetWindow()),
              eventer_(sg::GetEngine().GetEventer()),
              m_font(sg::GetEngine().CreateFont())
        {
            for (int i = 0; i < width / TILE.x; ++i)
            {
                for (int j = 0; j < hight / TILE.y; ++j)
                {
                    rects_.push_back({sg::IntRectType({{i * TILE.x, j * TILE.y}, TILE}), sg::TRANSPER_DARK_BLUE});
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
            DoRayCasting(endPoint);

            auto txt = boost::format("FPS: %ld {%d, %d} {%d, %d} %d") //
                       % (std::nano::den / duration.count())          //
                       % startPoint_.x                                //
                       % startPoint_.y                                //
                       % eventer_->MousePosition().x                  //
                       % eventer_->MousePosition().y                  //
                       % (angle_ ? *angle_ : 0)                       //
                ;

            m_font->PrintText(txt.str());
        }

        void DoRayCasting(olc::vf2d endPoint) // draw point of a first intersection
        {
            olc::vf2d vRayDir = (endPoint - startPoint_).norm();
            olc::vf2d vRayUnitStepSize = {std::sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)),
                                          std::sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y))};

            olc::vi2d vMapCheck = startPoint_;
            olc::vf2d vRayLength1D;
            olc::vi2d vStep;

            if (vRayDir.x < 0)
            {
                vStep.x = -1;
                vRayLength1D.x = (startPoint_.x - float(vMapCheck.x)) * vRayUnitStepSize.x;
            }
            else
            {
                vStep.x = 1;
                vRayLength1D.x = (float(vMapCheck.x + 1) - startPoint_.x) * vRayUnitStepSize.x;
            }

            if (vRayDir.y < 0)
            {
                vStep.y = -1;
                vRayLength1D.y = (startPoint_.y - float(vMapCheck.y)) * vRayUnitStepSize.y;
            }
            else
            {
                vStep.y = 1;
                vRayLength1D.y = (float(vMapCheck.y + 1) - startPoint_.y) * vRayUnitStepSize.y;
            }

            // Perform "Walk" until collision or range check
            bool bTileFound = false;
            float fMaxDistance = 100.0f;
            float fDistance = 0.0f;
            while (!bTileFound && fDistance < fMaxDistance)
            {
                // Walk along shortest path
                if (vRayLength1D.x < vRayLength1D.y)
                {
                    vMapCheck.x += vStep.x;
                    fDistance = vRayLength1D.x;
                    vRayLength1D.x += vRayUnitStepSize.x;
                }
                else
                {
                    vMapCheck.y += vStep.y;
                    fDistance = vRayLength1D.y;
                    vRayLength1D.y += vRayUnitStepSize.y;
                }

                // Test tile at new test point
                if (vMapCheck.x >= 0 && vMapCheck.x < TILE.x && vMapCheck.y >= 0 && vMapCheck.y < TILE.y)
                {
                    std::size_t i{vMapCheck.y * TILE.x + vMapCheck.x};
                    // assert(i < rects_.size());
                    if (rects_.size() < i && rects_[i].second == sg::DARK_BLUE)
                    {
                        bTileFound = true;
                    }
                }
            }

            if (bTileFound)
            {
                olc::vf2d vIntersection = startPoint_ + vRayDir * fDistance;
                renderer_->DrawCircle(vIntersection * TILE.x, 10, sg::YELLOW, true);
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

        int ToDegrees(olc::vi2d vec)
        {
            return std::atan2(vec.y, vec.x) * 180 / M_PI;
        }

    private:
        sg::IRenderer::Ptr renderer_;
        sg::IWindow::Ptr window_;
        sg::IEventer::Ptr eventer_;
        sg::IFont::Ptr m_font;
        olc::vf2d startPoint_{{}, {}};
        std::optional<int> angle_;
        std::vector<PairType> rects_;
    };
}
