#pragma once
#include "../EventManager.h"
class SwitchScene : public Event<ApplicationEvent> {
public:
    SwitchScene(int scene)
        : Event<ApplicationEvent>(ApplicationEvent::SWITCH_SCENE, scene, "change scene") {}
    virtual ~SwitchScene() = default;
public:
};