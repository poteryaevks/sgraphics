#pragma once

#include <boost/noncopyable.hpp>
#include <memory>
#include <functional>
#include <sgraphics/engine/IEvent.hpp>
#include <sgraphics/geometry/types.hpp>

#include <alm/common/event.h>

namespace sgraphics
{
    class IEventer : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<IEventer>;
        virtual bool OnUpdate() = 0;
        virtual ~IEventer() = default;

        virtual bool LeftMouseDown() const = 0;
        virtual bool LeftMouseUp() const = 0;
        virtual bool RightMouseDown() const = 0;
        virtual bool RightMouseUp() const = 0;
        virtual bool LeftMouseHold() const = 0;
        virtual bool RightMouseHold() const = 0;
        virtual bool SUp() const = 0;
        virtual bool SDown() const = 0;
        virtual bool AUp() const = 0;
        virtual bool ADown() const = 0;
        virtual bool WUp() const = 0;
        virtual bool WDown() const = 0;
        virtual bool DUp() const = 0;
        virtual bool DDown() const = 0;
        virtual bool DHold() const = 0;
        virtual bool AHold() const = 0;
        virtual bool SHold() const = 0;
        virtual bool WHold() const = 0;
        virtual MousePosType MousePosition() const = 0;
        virtual bool Quit() const = 0;

        template <class Object, class... TParams>
        void AddEventHandler(Object &object, void (Object::*method)(TParams...))
        {
            invoker_ += METHOD_HANDLER(object, method);
        }

    protected:
        alm::common::TEvent<IEvent::Ptr> invoker_;
    };
}
