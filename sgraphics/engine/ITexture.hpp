#pragma once

#include <boost/noncopyable.hpp>
#include <memory>

namespace sgraphics
{
    class ITexture
    {
    public:
        using Ptr = std::shared_ptr<ITexture>;
        virtual ~ITexture() = default;
    };
}
