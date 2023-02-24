#pragma once

#include <boost/noncopyable.hpp>
#include <memory>
#include <functional>
#include <sgraphics/engine/IEvent.hpp>

#include <alm/common/event.h>

namespace sgraphics
{
    class IFont : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<IFont>;
        virtual bool PrintText(const std::string& text) = 0;
        virtual ~IFont() = default;
    };
}
