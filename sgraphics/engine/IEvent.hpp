#pragma once

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

#include <sgraphics/geometry/types.hpp>

namespace sg
{
    enum class EventType
    {
        Unable,
        Quit,
        LeftMouseButtonDown,
        RightMouseButtonDown,
        LeftMouseButtonUp,
        RightMouseButtonUp
    };

    class IEvent : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<IEvent>;
        virtual ~IEvent() = default;
        virtual EventType GetType() const = 0;
        virtual MousePosType GetMousePosition() const = 0;
    };
}
