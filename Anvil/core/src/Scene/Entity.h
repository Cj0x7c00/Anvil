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

		template <typename Component, typename... Args>
		void AddComponent(Args&&... args); 

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

