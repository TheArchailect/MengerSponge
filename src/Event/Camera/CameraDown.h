#pragma once
#include "Event/EventManager.h"
class CameraDown : public Event<CameraEvent>
{
public:
    CameraDown(bool b_Update)
        : Event<CameraEvent>(CameraEvent::CAMERA_DOWN, b_Update, "camera translate event") {}
    virtual ~CameraDown() = default;
public:
};
