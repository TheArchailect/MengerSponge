#include "Scene.h"

Scene::Scene(int width, int height)
{
    b_IsActive = false;
    RegisterCallbacks();
	m_Camera = new Camera(width, height);
	Box* b = new Box(glm::vec3(0, 0, 0), 12);
	Subdivision = 1;
	MengerSponge = b->Generate();
}

// sub divide
void Scene::Generate()
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
}
