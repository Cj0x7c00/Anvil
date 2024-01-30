#pragma once
#include "Components.h"
#include "Entity.h"
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

		Ref<Entity> CreateEntity(std::string _name);
		void        DeleteEntity(Entity& _ent);
		Entity*     GetEntityByUUID(UuID uuid);

		Ref<entt::registry> GetRegistry();

		std::string GetName();

	private:
		std::string m_Name;

		Ref<entt::registry> m_Registry;
		friend class Entity;
	};
}
