#pragma once
#include "Entity.h"
#include "Components.h"
#include "../Base/macros.hpp"
#include "../Base/Pointer.hpp"
#include "../Util/anvLog.hpp"
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
		void        DeleteEntity(Entity& _ent);
		Entity*     GetEntityByUUID(UuID uuid);

		entt::registry& GetRegistry();

		std::string GetName();

	private:
		std::string m_Name;

		entt::registry m_Registry;
		friend class Entity;
	};
}
