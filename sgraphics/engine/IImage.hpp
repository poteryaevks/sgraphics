#pragma once

#include <boost/noncopyable.hpp>
#include <memory>

namespace sgraphics
{
    class IImage
    {
    public:
        using Ptr = std::shared_ptr<IImage>;
        virtual ~IImage() = default;
    };
}
