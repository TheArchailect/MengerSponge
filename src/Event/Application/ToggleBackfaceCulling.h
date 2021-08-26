#pragma once
#include "Event/EventManager.h"

class ToggleBackfaceCulling : public Event<ApplicationEvent> {
public:
    ToggleBackfaceCulling()
        : Event<ApplicationEvent>(ApplicationEvent::TOGGLE_BACKFACECULLING, "toggle backface event") {}
    virtual ~ToggleBackfaceCulling() = default;
public:
};
