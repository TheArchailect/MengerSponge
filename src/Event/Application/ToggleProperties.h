#pragma once
#include "Event/EventManager.h"
class ToggleProperties : public Event<ApplicationEvent> {
public:
    ToggleProperties()
        : Event<ApplicationEvent>(ApplicationEvent::TOGGLE_PROPERTIES, "toggle properties panel event") {}
    virtual ~ToggleProperties() = default;
public:
};