#pragma once
#include "../EventManager.h"
class ApplicationEnd : public Event<ApplicationEvent> {
public:
    ApplicationEnd()
        : Event<ApplicationEvent>(ApplicationEvent::APPLICATION_END, "end application") {}
    virtual ~ApplicationEnd() = default;
public:
};