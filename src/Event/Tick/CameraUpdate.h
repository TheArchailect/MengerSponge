#pragma once
#include "../EventManager.h"
class CameraUpdate : public Event<CameraEvent> {
public:
    CameraUpdate()
        : Event<CameraEvent>(CameraEvent::TICK, "camera tick event") {}
    virtual ~CameraUpdate() = default;
public:
};