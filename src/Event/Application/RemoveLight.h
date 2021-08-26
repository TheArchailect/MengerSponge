#pragma once
#include "Event/EventManager.h"

class RemoveLight : public Event<ApplicationEvent> {
public:
    RemoveLight()
        : Event<ApplicationEvent>(ApplicationEvent::REMOVE_LIGHT, "remove light event") {}
    virtual ~RemoveLight() = default;
public:
};
