#pragma once
#include "../Core/Application.h"
#include "../Core/Scenes/Scene.h"
#include "../Core/Scenes/ModernScene.h"
#include "../Core/Scenes/FixedFunctionScene.h"
#include "../Core/Scenes/GPUAnimatedGeometry.h"
#include "../Core/Scenes/CPUAnimatedGeometry.h"
#include "../Core/Scenes/InstancedGeometry.h"
#include "../Core/Scenes/InstancedGeometryGLSL.h"
#include "../Core/Overlay.h"
#include "../Core/include.h"

class MengerSponge : public Application
{
public:
    MengerSponge(uint32_t width, uint32_t height);
    void Run() override;   

private:
    void Init() override;
    void End(const Event<ApplicationEvent>& e) override;
    void Tick() override;

private:
    void RegisterCallbacks();
    void RenderFrame();
    void UpdateOverlay();
    std::vector<Scene*> m_Scenes;
    SCENE_NUMBER SceneNumber;
    OVERLAY_STATE OverlayState;
    Overlay* m_Overlay;

private:
    void ToggleOverlayDisplay(const Event<ApplicationEvent>& e);
    void ChangeScene(const Event<ApplicationEvent>& e);
};

