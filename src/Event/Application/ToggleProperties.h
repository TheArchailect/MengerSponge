#pragma once
#include "../EventManager.h"
class ToggleProperties : public Event<ApplicationEvent> {
public:
    ToggleProperties()
        : Event<ApplicationEvent>(ApplicationEvent::TOGGLE_PROPERTIES, "end application") {}
    virtual ~ToggleProperties() = default;
public:
};