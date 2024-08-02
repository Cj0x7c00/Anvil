#include "Scene.h"
#include "Components.h"
#include <entt/entt.hpp>
#include "Base/anvApplication.hpp"
#include "Renderer/Camera.h"

namespace Anvil
{
    Ref<Scene> Scene::Create(std::string _name)
    {
        auto new_scene = CreateRef<Scene>(_name);
        SceneManager::NewSceneCreated(new_scene);
        return new_scene;
    }

    Scene::Scene(std::string _name)
        : m_Name{ _name }
    {
        m_ActiveCamera = CreateEntity("Main Camera");
        m_ActiveCamera->AddComponent<Camera>();
        ENGINE_INFO("Created Scene: {}", _name);
    }

    Ref<Entity> Scene::CreateEntity(std::string _name)
    {
        return CreateRef<Entity>(m_Registry, _name);
    }

    Ref<Entity> Scene::CreateEntity(std::string _name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    {
        return CreateRef<Entity>(m_Registry, _name, position, rotation, scale);
    }

    Ref<Canvas> Scene::CreateCanvas()
    {
        auto& entity = CreateEntity("Canvas");
        auto& canvas = entity->AddComponent<CanvasComponent>();
        return canvas.Get();
    }

    void Scene::DeleteEntity(Entity& _ent)
    {
        m_Registry.destroy(_ent.Get());
    }

    Entity* Scene::GetEntityByUUID(UuID uuid)
    {
        // Find the UUID component that mached the UUID specified
        Entity* ent = nullptr;

        m_Registry.view<UUIDComponent>().each(
        [this, &ent, &uuid](entt::entity entity, UUIDComponent& comp)
        {
            // Get the user pointer (Anvil::Entity) and return its value
            if (comp.Get() == uuid.GetUUID())
            {
                auto Ent = m_Registry.get<UserPointerComponent>(entity);
                ent = Ent.Get();
            }
        });

        return ent;
    }

    entt::registry& Scene::GetRegistry()
    {
        return m_Registry;
    }

    std::string Scene::GetName()
    {
        return m_Name;
    }
}
