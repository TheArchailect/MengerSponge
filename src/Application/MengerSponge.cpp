#include "MengerSponge.h"

MengerSponge::MengerSponge(unsigned int width, unsigned int height) : Application(width, height)
{
    std::cout << "Application sub-class constructor" << std::endl;
    Init();
    RegisterCallbacks();
    // material setup, needs to be moved out of here 
    float ambient[4] = { 0.0f, 0.1f, 0.06f, 1.0f };
    float diffuse[4] = { 0.0f,0.50980392f,0.50980392f,1.0f };
    float specular[4] = { 0.50196078f,0.50196078f,0.50196078f,1.0f };
    float shine = 32.0f;
    // material end
    CyanPlastic = new Material(ambient, diffuse, specular, shine);
    SceneNumber = SCENE_NUMBER::S_ONE;
    OverlayState = OVERLAY_STATE::S_FPS_ONLY;
    m_Overlay = new Overlay();
}

void MengerSponge::Tick()
{
    super::GetUtils().DeltaTime();
    super::GetUtils().FrameRate();
    CameraUpdate e;
    m_EventManager->CameraDispatcher.Post(e);
    super::Clear();
    m_Overlay->Render(OverlayState);
    RenderFrame();
    super::m_Input->Update();
    // update overlay could be somewhere else
    {
        m_Overlay->m_OverlayData->Resolution = glm::vec2(800, 600); // TO DO
        m_Overlay->m_OverlayData->GeometrySize = m_Scenes.at(SceneNumber)->GeometrySize();
        m_Overlay->m_OverlayData->LOD = m_Scenes.at(SceneNumber)->Subdivision;
        m_Overlay->m_OverlayData->BackFaceCulling = false; // TO DO
        m_Overlay->m_OverlayData->DepthBuffering = true;
        m_Overlay->m_OverlayData->LightCount = 1; // TO DO
        m_Overlay->m_OverlayData->SceneNumber = SceneNumber; // TO DO
        m_Overlay->m_OverlayData->RefreshRate = "60hz"; // TO DO
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
    //super::SetMaterial(*CyanPlastic); // only in fixed function
    m_Scenes.at(SceneNumber)->Render();
}

void MengerSponge::ToggleOverlayDisplay(const Event<ApplicationEvent>& e)
{
    if (OverlayState == OVERLAY_STATE::S_FPS_ONLY) OverlayState = OVERLAY_STATE::S_FULL_HUD;
    else OverlayState = OVERLAY_STATE::S_FPS_ONLY;
}

void MengerSponge::ChangeScene(const Event<ApplicationEvent>& e)
{
    //close glad & re initialise
    m_Scenes.at(SceneNumber)->End();
    SceneNumber = (SCENE_NUMBER)e.scene; //this cannot be done until the scenes exist
    m_Scenes.at(SceneNumber)->Begin();
    std::cout << e.scene << std::endl;
}

bool MengerSponge::Init()
{
    m_Scenes.resize(6);
    m_Scenes.at(SCENE_NUMBER::S_ONE) = new FixedFunctionScene
    (
        super::GetWindow().GetWidth(), 
        super::GetWindow().GetHeight()
    );
    m_Scenes.at(SCENE_NUMBER::S_ONE)->Begin();
    m_Scenes.at(SCENE_NUMBER::S_TWO) = new ModernScene
    (
        super::GetWindow().GetWidth(),
        super::GetWindow().GetHeight()
    );
    return true; // do some checks here to asset all scenes are initialised
}

void MengerSponge::Run()
{
    std::cout << "Application subclass run" << std::endl;
    while (super::b_IsRunning)
    {
        Tick(); // maybe replace with a tick event creation?
    }
}

void MengerSponge::End(const Event<ApplicationEvent>& e)
{
    std::cout << "Application subclass deconstructor" << std::endl;
    super::b_IsRunning = false;
    super::End(e);
}