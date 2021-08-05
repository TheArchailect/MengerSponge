#pragma once
#include "../EventManager.h"

    class CameraRight : public Event<CameraEvent>
    {
    public:
        CameraRight(bool b_Update)
            : Event<CameraEvent>(CameraEvent::CAMERA_RIGHT, b_Update, "camera translate event") {}
        virtual ~CameraRight() = default;
    public:
    };
