#pragma once
#include "../UI/Canvas.h"
#include "../Base/macros.hpp"
#include "../Base/Pointer.hpp"
#include "../Util/anvLog.hpp"
#include "../UUID/uuid.h"
#include "Entity.h"
#include <entt/entt.hpp>
#include <string>

namespace Anvil
{

	class ANV_API Scene
	{
	public:
		static Ref<Scene> Create(std::string _name);

		Scene(std::string _name);

		Ref<Entity> CreateEntity(std::string _name="New Object");

		Ref<Entity> CreateEntity(std::string _name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		Ref<Canvas> CreateCanvas();

		
		Entity*     GetEntityByUUID(UuID uuid);
		void        DeleteEntity(Entity& _ent);

		template<typename Component>
		entt::view<Component> GetEntitiesWithComponent()
		{
			return m_Registry.view<Component>();
		}

		entt::registry& GetRegistry();

		Ref<Entity> GetActiveCamera() {
			return m_ActiveCamera;
		}

		std::string GetName();

	private:

		std::string m_Name;
		entt::registry m_Registry;

		Ref<Entity> m_ActiveCamera;

		friend class Entity;
	};
}
