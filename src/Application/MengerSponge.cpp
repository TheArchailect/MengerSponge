#include "MengerSponge.h"

MengerSponge::MengerSponge(uint32_t width, uint32_t height) : Application(width, height)
{
    RegisterCallbacks();
    SceneNumber = SCENE_NUMBER::S_ONE;
    OverlayState = OVERLAY_STATE::S_FPS_ONLY;
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

// application subclass subscription to app events
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
    m_Overlay->m_OverlayData->Resolution = glm::vec2(1920, 1080); // TO DO
    m_Overlay->m_OverlayData->GeometrySize = m_Scenes.at(SceneNumber)->GeometrySize();
    m_Overlay->m_OverlayData->LOD = m_Scenes.at(SceneNumber)->CurrentSubdivision + 1; // 0 is 1 subdivision
    m_Overlay->m_OverlayData->BackFaceCulling = true; // TO DO
    m_Overlay->m_OverlayData->DepthBuffering = true;
    m_Overlay->m_OverlayData->LightCount = 1; // TO DO
    m_Overlay->m_OverlayData->SceneNumber = SceneNumber; // TO DO
    m_Overlay->m_OverlayData->RefreshRate = "60hz"; // TO DO
    m_Overlay->m_OverlayData->TriCount = m_Scenes.at(SceneNumber)->TriangleCount();
}

void MengerSponge::ToggleOverlayDisplay(const Event<ApplicationEvent>& e)
{
    if (OverlayState == OVERLAY_STATE::S_FPS_ONLY) OverlayState = OVERLAY_STATE::S_FULL_HUD;
    else OverlayState = OVERLAY_STATE::S_FPS_ONLY;
}

void MengerSponge::ChangeScene(const Event<ApplicationEvent>& e)
{
    m_Scenes.at(SceneNumber)->End();
    SceneNumber = e.SceneNumber;
    m_Scenes.at(SceneNumber)->Begin();
}

bool MengerSponge::Init()
{
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
    m_Scenes.at(SceneNumber)->Begin();
    return true; // do some checks here to asset all scenes are initialised
}

void MengerSponge::Run()
{
    while (super::b_IsRunning)
    {
        Tick();
    }
}

void MengerSponge::End(const Event<ApplicationEvent>& e)
{
    super::b_IsRunning = false;
    super::End(e);
    m_Scenes.clear();
    delete m_Overlay;
}