#pragma once
#include "../EventManager.h"
class WindowClosedEvent : public Event<WindowEvent>
{
public:
    WindowClosedEvent() : Event<WindowEvent>(WindowEvent::WINDOW_CLOSE) {}
    virtual ~WindowClosedEvent() = default;
};