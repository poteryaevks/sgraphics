#pragma once

#pragma once

#include <boost/noncopyable.hpp>

#include <functional>

#include "sgraphics/geometry/types.hpp"
#include "../ICollision.hpp"

namespace sgraphics
{
    class StaticCollision final: public ICollision
    {
    public:
        StaticCollision();
        ~StaticCollision() override;

        bool Calculate(FRectType &rect, const RectsType &rects, float time) override;
        RectsType GetContacts() const override;
    };

    class DynamicCollision final: public ICollision
    {
    public:
        DynamicCollision();
        ~DynamicCollision() override;

        bool Calculate(FRectType &rect, const RectsType &rects, float time) override;
        RectsType GetContacts() const override;
    };

    class DynamicCollision2 final: public ICollision
    {
    public:
        DynamicCollision2();
        ~DynamicCollision2() override;

        bool Calculate(FRectType &rect, const RectsType &rects, float time) override;
        RectsType GetContacts() const override;
    };
}
