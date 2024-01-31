#pragma once
#include "Components.h"
#include "../Base/Pointer.hpp"
#include "../Base/macros.hpp"
#include <entt/entt.hpp>

namespace Anvil
{
	
	class ANV_API Entity
	{
	public:
		Entity(entt::registry& _reg, std::string _name);
		Entity();

		template <typename Component, typename... Args>
		Component& AddComponent(Args&&... args)
		{
			return m_Reg.emplace<Component>(m_Entity, std::forward<Args>(args)...);
		}

		template<typename Component>
		void RemoveComponent();

		entt::entity& Get() { return m_Entity; }

	private:
		void set_user_pointer();

	private:
		entt::entity    m_Entity;
	    entt::registry& m_Reg;
	};
}

