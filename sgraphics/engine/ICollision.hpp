#pragma once

#include <boost/noncopyable.hpp>
#include <vector>
#include <memory>

#include <sgraphics/geometry/types.hpp>

namespace sgraphics
{
    enum class CollisionType
    {
        Dynamic, // deprecated
        Static,
        Dynamic2
    };
    
    class ICollision : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<ICollision>;
        using RectsType = std::vector<FRectType*>;

        static Ptr Create(CollisionType);
        virtual RectsType GetContacts() const = 0;
        virtual bool Calculate(FRectType &rect, const RectsType &rects, float time) = 0;
        virtual ~ICollision() = default;
    };
}
