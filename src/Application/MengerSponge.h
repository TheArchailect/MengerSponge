#pragma once
#include "../Core/Application.h"
#include "../Core/Scene.h"

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
    void RenderOverlay();
    Scene* m_Scene;
    GLTtext* fps;
};

