#pragma once

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

#include <sgraphics/geometry/types.hpp>

namespace sg
{
    enum class CommandEvent
    {
        None,
        Quit,
    };

    enum class KeyboardEvent
    {
        None,
        SDown,
        SUp,
        WDown,
        WUp,
        ADown,
        AUp,
        DDown,
        DUp,
        SHold,
        WHold,
        AHold,
        DHold,
    };

    enum class MouseEvent
    {
        None,
        LeftDown,
        RightDown,
        LeftUp,
        RightUp,
        LeftHold,
        RightHold
    };

    class IEvent : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<IEvent>;
        virtual ~IEvent() = default;
        virtual void Update() = 0;
        virtual KeyboardEvent GetKeyboardEvent() const = 0;
        virtual MouseEvent GetMouseEvent() const = 0;
        virtual CommandEvent GetCommandEvent() const = 0;
        virtual const MousePosType &GetMousePosition() const = 0;
    };
}
