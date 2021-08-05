#pragma once
#include "../EventManager.h"

class CameraLeft : public Event<CameraEvent>
    {
    public:
        CameraLeft(bool b_Update)
            : Event<CameraEvent>(CameraEvent::CAMERA_LEFT, b_Update, "camera translate event") {}
        virtual ~CameraLeft() = default;
    public:
    };

