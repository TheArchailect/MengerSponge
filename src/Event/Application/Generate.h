#pragma once
#include "../EventManager.h"

class Generate : public Event<ApplicationEvent> {
public:
    Generate()
        : Event<ApplicationEvent>(ApplicationEvent::GENERATE, "generate geometry event") {}
    virtual ~Generate() = default;
public:
};
