#pragma once
#include "Event/EventManager.h"
class CameraForward : public Event<CameraEvent>
{
public:
	CameraForward(bool b_Update)
	: Event<CameraEvent>(CameraEvent::CAMERA_FORWARD, b_Update, "camera translate event") {}
	virtual ~CameraForward() = default;
public:
};
