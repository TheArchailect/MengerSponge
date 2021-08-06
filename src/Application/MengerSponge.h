#pragma once
#include "../Core/Application.h"
#include "../Core/Scenes/Scene.h"
#include "../Core/Scenes/ModernScene.h"
#include "../Core/Scenes/FixedFunctionScene.h"
#include "../Core/Overlay.h"
#include "../Core/include.h"

enum SCENE_NUMBER {
    S_ONE, 
    S_TWO,
    S_THREE,
    S_FOUR,
    S_FIVE,
    S_SIX,
};

class MengerSponge : public Application
{
public:
    MengerSponge(unsigned int width, unsigned int height);
    bool Init() override;
    void Run() override;
    void End(const Event<ApplicationEvent>& e) override;
    void Tick() override;

private:
    void RegisterCallbacks();
    void RenderFrame();
    std::vector<Scene*> m_Scenes;
    SCENE_NUMBER SceneNumber;
    OVERLAY_STATE OverlayState;
    Overlay* m_Overlay;
    Material* CyanPlastic;	

private:
    void ToggleOverlayDisplay(const Event<ApplicationEvent>& e);
    void ChangeScene(const Event<ApplicationEvent>& e);
};

