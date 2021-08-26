#pragma once
#include "Core/include.h"
struct CAMERA_ROTATION
{
    float yaw = 0;
    float pitch = 0;
};

enum SCENE_NUMBER {
    S_ONE,
    S_TWO,
    S_THREE,
    S_FOUR,
    S_FIVE,
    S_SIX,
};

template <typename T>
class Event 
{
protected:
    T EventType;
    std::string EventName;
public:
    Event(T type, const std::string& name)                                : EventType(type), EventName(name) {};
    Event(T type, SCENE_NUMBER scene, const std::string& name)            : EventType(type), EventName(name), SceneNumber(scene) {};
    Event(T type, int d, const std::string& name)                         : EventType(type), EventName(name), division(d) {};
    Event(T type, int w, int h, const std::string& name)                  : EventType(type), EventName(name), windowWidth(w), windowHeight(h) {};
    Event(T type, CAMERA_ROTATION rotation, const std::string& name)      : EventType(type), EventName(name), m_CameraRotation(rotation) {};
    Event(T type, bool b_Update, const std::string& name)                 : EventType(type), EventName(name), b_CameraUpdate(b_Update) {};

public:
    inline const T Type() const { return EventType; };
    inline const std::string& GetName() const { return EventName; };
    virtual bool IsHandled() { return b_Handled; };

public:
    bool b_Handled = false;
    int windowWidth = 0;
    int windowHeight = 0;
    CAMERA_ROTATION m_CameraRotation;
    SCENE_NUMBER SceneNumber = SCENE_NUMBER::S_ONE;
    bool b_CameraUpdate = false;
    int division = 0;

};
    
template<typename T>
class Dispatcher {
private:
    using SlotType = std::function<void(const Event<T>&)>;
    std::map<T, std::vector<SlotType>> Observers;
public:
    void Subscribe(T type, const SlotType& funct) {
        Observers[type].push_back(funct);
    };
    void Post(Event<T>& event) {
        if (Observers.find(event.Type()) == Observers.end()) return;
        for (auto&& observer : Observers.at(event.Type())) {
            if (!event.b_Handled) observer(event);
        }
    };
};

