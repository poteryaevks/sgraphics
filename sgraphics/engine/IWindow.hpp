#pragma once

#include <boost/noncopyable.hpp>
#include <memory>

namespace sgraphics
{
    class IWindow : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<IWindow>;
        virtual int GetHeight() const = 0;
        virtual int GetWidth() const = 0;
        virtual ~IWindow() = default;
    };
}
