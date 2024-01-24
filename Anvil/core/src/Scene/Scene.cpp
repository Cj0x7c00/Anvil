#include "Scene.h"
#include "Entity.h"

namespace Anvil
{
    Ref<Scene> Scene::Create()
    {
        return CreateRef<Scene>();
    }

    Ref<Entity> Scene::CreateEntity()
    {
        return CreateRef<Entity>();
    }
}
