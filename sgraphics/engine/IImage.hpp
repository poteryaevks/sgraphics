#pragma once

#include <boost/noncopyable.hpp>
#include <memory>

namespace sg
{
    class IImage
    {
    public:
        using Ptr = std::shared_ptr<IImage>;
        virtual ~IImage() = default;
    };
}
