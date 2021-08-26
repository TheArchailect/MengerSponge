#pragma once
#include "Event/EventManager.h"

class Generate : public Event<ApplicationEvent> {
public:
    Generate(int division)
        : Event<ApplicationEvent>(ApplicationEvent::GENERATE, division, "generate geometry event") {}
    virtual ~Generate() = default;
public:
};
