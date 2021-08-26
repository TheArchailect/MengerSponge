#pragma once
#include "Event/EventManager.h"

class AddLight : public Event<ApplicationEvent> {
public:
    AddLight()
        : Event<ApplicationEvent>(ApplicationEvent::ADD_LIGHT, "generate light event") {}
    virtual ~AddLight() = default;
public:
};
