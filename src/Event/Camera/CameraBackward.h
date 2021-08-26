#pragma once
#include "Event/EventManager.h"

class CameraBackward : public Event<CameraEvent> {
public:
    CameraBackward(bool b_Update)
        : Event<CameraEvent>(CameraEvent::CAMERA_BACKWARD, b_Update, "camera translate event") {}
    virtual ~CameraBackward() = default;
public:
};
