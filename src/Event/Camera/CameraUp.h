#pragma once
#include "../EventManager.h"

    class CameraUp : public Event<CameraEvent>
    {
    public:
        CameraUp(bool b_Update)
            : Event<CameraEvent>(CameraEvent::CAMERA_UP, b_Update, "camera translate event") {}
        virtual ~CameraUp() = default;
    public:
    };
