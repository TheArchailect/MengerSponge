#include "Scene.h"

Scene::Scene(int width, int height)
{
    RegisterCallbacks();
	m_Camera = new Camera(width, height);
	Box* b = new Box(glm::vec3(0, 0, 0), 10);
	Subdivision = 0;
	MengerSponge = b->Generate();
}

void Scene::Generate(const Event<ApplicationEvent>& e)
{
    std::vector<Box*> generated;
    for (Box* b : MengerSponge)
    {
        std::vector<Box*> temp = b->Generate();
        for (Box* tb : temp)
        {
            generated.push_back(tb);
        }
    }
    MengerSponge = generated;
    Subdivision++;
}

int Scene::GeometrySize()
{
    return sizeof(Box) * MengerSponge.size();
}

void Scene::RegisterCallbacks()
{
    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::GENERATE,
        std::bind
        (
            &Scene::Generate,
            this,
            std::placeholders::_1
        )
    );
}
