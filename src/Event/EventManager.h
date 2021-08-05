#pragma once
#include "Event.h"
#include "../Core/include.h"

#include "Window/WindowEvent.h"
#include "Window/WindowClosedEvent.h"
#include "Window/WindResizeEvent.h"

#include "Camera/CameraEvent.h"
#include "Camera/CameraRotate.h"
#include "Camera/CameraViewportResize.h"

#include "Camera/CameraBackward.h"
#include "Camera/CameraDown.h"
#include "Camera/CameraForward.h"
#include "Camera/CameraLeft.h"
#include "Camera/CameraRight.h"
#include "Camera/CameraUp.h"

#include "Tick/CameraUpdate.h"

#include "Application/ApplicationEvent.h"
#include "Application/Generate.h"
#include "Application/ApplicationEnd.h"

class EventManager {
public:
	EventManager();
	Dispatcher<WindowEvent> WindowDispatcher;
	Dispatcher<CameraEvent> CameraDispatcher;
	Dispatcher<ApplicationEvent> ApplicationDispatcher;
	static inline EventManager& Get() { return *s_Instance; }
private:
	static EventManager* s_Instance;
};
