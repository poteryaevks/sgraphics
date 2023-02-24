#include "CollisionImpl.hpp"

#include <iostream>

namespace sgraphics
{
    StaticCollision::StaticCollision() = default;
    StaticCollision::~StaticCollision() = default;

    bool StaticCollision::Calculate(FRectType &rect, const RectsType &rects, float time)
    {
        for (auto &r : rects)
        {
            if (olc::aabb::RectVsRect(r, &rect))
            {
                if (rect.pos != r->pos)
                {
                    rect.pos -= rect.vel * time;
                    rect.vel = {0, 0};
                    return true;
                }
            }
        }

        return false;
    }

    ICollision::RectsType StaticCollision::GetContacts() const { return {}; }

    ////////////////////////////////////////////////

    DynamicCollision::DynamicCollision() = default;
    DynamicCollision::~DynamicCollision() = default;

    bool DynamicCollision::Calculate(FRectType &rect, const RectsType &rects, float time)
    {
        std::vector<FRectType*> contacts;
        olc::vf2d cp, cn;
        float t = 0;

        for (const auto &r : rects)
        {
            if (olc::aabb::DynamicRectVsRect(&rect, time, *r, cp, cn, t))
                contacts.push_back(const_cast<FRectType *>(r));
        }

        for (auto &contact : contacts)
        {
            if (olc::aabb::DynamicRectVsRect(&rect, time, *contact, cp, cn, t))
            {
                rect.contact[0] = cn.y > 0 ? contact : nullptr;
                rect.contact[1] = cn.x < 0 ? contact : nullptr;
                rect.contact[2] = cn.y < 0 ? contact : nullptr;
                rect.contact[3] = cn.x > 0 ? contact : nullptr;

                rect.vel += cn * olc::vf2d(std::abs(rect.vel.x), std::abs(rect.vel.y)) * (1 - t);
                return true;
            }
        }

        return false;
    }

    ICollision::RectsType DynamicCollision::GetContacts() const { return {}; }

    ////////////////////////////////////////////////

    DynamicCollision2::DynamicCollision2() = default;
    DynamicCollision2::~DynamicCollision2() = default;

    bool DynamicCollision2::Calculate(FRectType &rect, const RectsType &rects, float fElapsedTime)
    {
        using PairType = std::pair<int, float>;
        bool result{false};
        // Sort collisions in order of distance
        olc::vf2d cp, cn;
        float t {}; //min_t = std::numeric_limits<float>::max();
        std::vector<PairType> z;

        // Work out collision point, add it to vector along with rect ID
        for (size_t i = 0; i < rects.size(); i++)
        {
            if (olc::aabb::DynamicRectVsRect(&rect, fElapsedTime, *rects[i], cp, cn, t))
            {
                z.push_back({i, t});
            }
        }

        // Do the sort
        std::sort(z.begin(), z.end(), [](const auto &a, const auto &b)
                  { return a.second < b.second; });

        // Now resolve the collision in correct order
        for (const auto& [key, value] : z)
        {
            olc::aabb::ResolveDynamicRectVsRect(&rect, fElapsedTime, rects[key]);
            result = true;
        }

        return result;
    }

    ICollision::RectsType DynamicCollision2::GetContacts() const { return {}; }

    ///////////////////////////////////////////////////////

    ICollision::Ptr ICollision::Create(CollisionType type)
    {
        try
        {
            switch (type)
            {
            case CollisionType::Static:
            {
                return ICollision::Ptr(new StaticCollision);
                break;
            }
            case CollisionType::Dynamic:
            {
                return ICollision::Ptr(new DynamicCollision);
                break;
            }
            case CollisionType::Dynamic2:
            {
                return ICollision::Ptr(new DynamicCollision2);
                break;
            }

            default:
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return nullptr;
    }
}
