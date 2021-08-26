#pragma once
#include "Event/EventManager.h"
class CameraViewportResize : public Event<CameraEvent>
{
public:
    CameraViewportResize(int w, int h)
    : Event<CameraEvent>(CameraEvent::VIEWPORT_RESIZE, w, h, "viewport resize") {}
    virtual ~CameraViewportResize() = default;
};

