#pragma once
#include "Event/EventManager.h"

class ToggleLighting : public Event<ApplicationEvent> {
public:
    ToggleLighting()
        : Event<ApplicationEvent>(ApplicationEvent::TOGGLE_LIGHTING, "toggle light event") {}
    virtual ~ToggleLighting() = default;
public:
};
