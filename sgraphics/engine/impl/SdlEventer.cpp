#include "SdlEventer.hpp"
#include "SdlEvent.hpp"

namespace sg
{
    SdlEventer::SdlEventer() = default;
    SdlEventer::~SdlEventer() = default;

    bool SdlEventer::OnUpdate()
    {
        SDL_PollEvent(&event_);
        invoker_(std::make_shared<SdlEvent>(event_));
        return true;
    };

}
