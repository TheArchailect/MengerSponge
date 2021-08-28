#include "MengerSponge.h"

MengerSponge::MengerSponge(uint32_t width, uint32_t height) 
    : Application(width, height)
{
    RegisterCallbacks();
    SceneNumber = SCENE_NUMBER::S_SIX;
    OverlayState = OVERLAY_STATE::S_FULL_HUD;
    m_Overlay = new Overlay();
}

void MengerSponge::Tick()
{
    if (b_IsRunning)
    {
        super::GetUtils().DeltaTime();
        super::GetUtils().FrameRate();                
        UpdateOverlay();                               
        CameraUpdate e;                              
        m_EventManager->CameraDispatcher.Post(e);      
        super::Clear();                                 
        m_Overlay->Render(OverlayState);           
        RenderFrame();
        super::m_Input->Update();          
    }
}

void MengerSponge::RegisterCallbacks()
{
    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::APPLICATION_END,
        std::bind
        (
            &MengerSponge::End,
            this,
            std::placeholders::_1
        )
    );

    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::TOGGLE_PROPERTIES,
        std::bind
        (
            &MengerSponge::ToggleOverlayDisplay,
            this,
            std::placeholders::_1
        )
    );

    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::SWITCH_SCENE,
        std::bind
        (
            &MengerSponge::ChangeScene,
            this,
            std::placeholders::_1
        )
    );
}

void MengerSponge::RenderFrame()
{
    m_Scenes.at(SceneNumber)->Render();
}

void MengerSponge::UpdateOverlay()
{
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    m_Overlay->m_OverlayData->Resolution = glm::vec2
    (
        super::m_Window.get()->GetWidth(),
        super::m_Window.get()->GetHeight()
    );
    m_Overlay->m_OverlayData->GeometrySize = m_Scenes.at(SceneNumber)->GeometrySize();
    m_Overlay->m_OverlayData->LOD = m_Scenes.at(SceneNumber)->CurrentSubdivision + 1;
    m_Overlay->m_OverlayData->BackFaceCulling = super::b_BackFaceCulling;
    m_Overlay->m_OverlayData->DepthBuffering = super::b_DepthTesting;
    m_Overlay->m_OverlayData->LightCount = m_Scenes.at(SceneNumber)->m_LightCount; 
    m_Overlay->m_OverlayData->SceneNumber = SceneNumber + 1;
    m_Overlay->m_OverlayData->RefreshRate = current.refresh_rate;
    m_Overlay->m_OverlayData->TriCount = m_Scenes.at(SceneNumber)->TriangleCount();
    m_Overlay->m_OverlayData->VertCount = m_Scenes.at(SceneNumber)->m_VertCount;
    m_Overlay->m_OverlayData->Lighting = super::b_Lighting;
}

void MengerSponge::ToggleOverlayDisplay(const Event<ApplicationEvent>& e)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "%s", e.GetName().c_str());
    if (OverlayState == OVERLAY_STATE::S_FPS_ONLY) OverlayState = OVERLAY_STATE::S_FULL_HUD;
    else OverlayState = OVERLAY_STATE::S_FPS_ONLY;
}

void MengerSponge::ChangeScene(const Event<ApplicationEvent>& e)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "%s", e.GetName().c_str());
    m_Scenes.at(SceneNumber)->End();
    SceneNumber = e.SceneNumber;
    m_Scenes.at(SceneNumber)->Begin();
}

void MengerSponge::End(const Event<ApplicationEvent>& e)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "%s", e.GetName().c_str());
    super::b_IsRunning = false;
    super::End(e);
    m_Scenes.clear();
    delete m_Overlay;
}

void MengerSponge::Init()
{
    super::Init();
    m_Scenes.resize(6);
    m_Scenes.at(SCENE_NUMBER::S_ONE) = new FixedFunctionScene
    (
        super::GetWindow().GetWidth(), 
        super::GetWindow().GetHeight()
    );
    m_Scenes.at(SCENE_NUMBER::S_TWO) = new ModernScene
    (
        super::GetWindow().GetWidth(),
        super::GetWindow().GetHeight()
    );
    m_Scenes.at(SCENE_NUMBER::S_THREE) = new InstancedGeometry
    (
        super::GetWindow().GetWidth(),
        super::GetWindow().GetHeight()
    );
    m_Scenes.at(SCENE_NUMBER::S_FOUR) = new InstancedGeometryGLSL
    (
        super::GetWindow().GetWidth(),
        super::GetWindow().GetHeight()
    );
    m_Scenes.at(SCENE_NUMBER::S_FIVE) = new CPUAnimatedGeometry
    (
        super::GetWindow().GetWidth(),
        super::GetWindow().GetHeight()
    );
    m_Scenes.at(SCENE_NUMBER::S_SIX) = new GPUAnimatedGeometry
    (
        super::GetWindow().GetWidth(),
        super::GetWindow().GetHeight()
    );
    m_Scenes.at(SceneNumber)->Begin();
}

void MengerSponge::Run()
{
    while (super::b_IsRunning)
    {
        Tick();
    }
}