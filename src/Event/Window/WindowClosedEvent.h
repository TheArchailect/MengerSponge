#pragma once
#include "Event/EventManager.h"
class WindowClosedEvent : public Event<WindowEvent>
{
public:
    WindowClosedEvent() : Event<WindowEvent>(WindowEvent::WINDOW_CLOSE, "window close event") {}
    virtual ~WindowClosedEvent() = default;
};