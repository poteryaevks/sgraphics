#pragma once

#include <boost/noncopyable.hpp>
#include <memory>
#include <functional>
#include <sgraphics/engine/IEvent.hpp>

#include <alm/common/event.h>

namespace sg
{
    class IEventer : private boost::noncopyable
    {
    public:
        using Ptr = std::shared_ptr<IEventer>;
        virtual bool OnUpdate() = 0;
        virtual ~IEventer() = default;

        template <class Object, class... TParams>
        void AddEventHandler(Object &object, void (Object::*method)(TParams...))
        {
            invoker_ += METHOD_HANDLER(object, method);
        }

    protected:
        alm::common::TEvent<IEvent::Ptr> invoker_;
    };
}
