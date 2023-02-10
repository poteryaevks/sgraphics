#pragma once

#include <boost/noncopyable.hpp>
#include <memory>

namespace sg
{
    class ITexture
    {
    public:
        using Ptr = std::shared_ptr<ITexture>;
        virtual ~ITexture() = default;
    };
}
