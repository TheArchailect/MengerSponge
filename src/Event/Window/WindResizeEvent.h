#pragma once
#include "Event/EventManager.h"
class WindowResizeEvent : public Event<WindowEvent>
{
public:
    WindowResizeEvent(int w, int h)
    : Event<WindowEvent>(WindowEvent::WINDOW_RESIZE, w, h, "window resize event") {}
    virtual ~WindowResizeEvent() = default;
};
