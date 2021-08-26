#pragma once
#include "Event/EventManager.h"

class ToggleDepthBuffer : public Event<ApplicationEvent> {
public:
    ToggleDepthBuffer()
        : Event<ApplicationEvent>(ApplicationEvent::TOGGLE_DEPTHBUFFER, "toggle depth event") {}
    virtual ~ToggleDepthBuffer() = default;
public:
};
