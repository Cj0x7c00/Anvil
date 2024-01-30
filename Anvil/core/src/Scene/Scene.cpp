#include "Scene.h"
#include <entt/single_include/entt/entt.hpp>

namespace Anvil
{
    Ref<Scene> Scene::Create(std::string _name="New Scene")
    {
        return CreateRef<Scene>(_name);
    }

    Scene::Scene(std::string _name)
        : m_Name{ _name }
    {
        ENGINE_INFO("Created Scene: {}", _name);
    }

    Ref<Entity> Scene::CreateEntity(std::string _name)
    {
        return CreateRef<Entity>(m_Registry, _name);
    }

    void Scene::DeleteEntity(Entity& _ent)
    {
        m_Registry->destroy(_ent.Get());
    }

    Entity* Scene::GetEntityByUUID(UuID uuid)
    {
        // Find the UUID component that mached the UUID specified
        Entity* ent = nullptr;

        m_Registry->view<UUIDComponent>().each(
        [this, &ent, &uuid](entt::entity entity, UUIDComponent& comp)
        {
            // Get the user pointer (Anvil::Entity) and return its value
            if (comp.Get() == uuid.GetUUID())
            {
                auto Ent = m_Registry->get<UserPointerComponent>(entity);
                ent = Ent.Get();
            }
        });

        return ent;
    }

    Ref<entt::registry> Scene::GetRegistry()
    {
        return m_Registry;
    }

    std::string Scene::GetName()
    {
        return m_Name;
    }
}
