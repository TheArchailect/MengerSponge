#pragma once
#include "Event/EventManager.h"

class CameraRotate : public Event<CameraEvent>
{
public:
    CameraRotate(CAMERA_ROTATION rotation)
    : Event<CameraEvent>(CameraEvent::CAMERA_ROTATION, rotation, "camera rotate") {}
    virtual ~CameraRotate() = default;
public:
};

