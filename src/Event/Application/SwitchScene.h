#pragma once
#include "Event/EventManager.h"
class SwitchScene : public Event<ApplicationEvent> {
public:
    SwitchScene(SCENE_NUMBER scene)
        : Event<ApplicationEvent>(ApplicationEvent::SWITCH_SCENE, scene, "change scene event") {}
    virtual ~SwitchScene() = default;
public:
};