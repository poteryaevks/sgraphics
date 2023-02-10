#pragma once

#include <sgraphics/geometry/types.hpp>

#include <boost/noncopyable.hpp>

#include <filesystem>
#include <memory>

namespace sg
{
    class ISprite : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<ISprite>;
        virtual void RenderCopy(const FloatRectType &src, const FloatRectType &dest) = 0;
        virtual void RenderCopy(const IntRectType &src, const IntRectType &dest) = 0;
        virtual ~ISprite() = default;
    };
}
