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
		Entity(Ref<entt::registry> _reg, std::string _name)
			: m_Reg{ _reg }
		{
			AddComponent<TagComponent>(_name);
			AddComponent<UUIDComponent>();
			set_user_pointer();
		}

		template <typename Component, typename... Args>
		void AddComponent(Args&&... args); 

		template<typename Component>
		void RemoveComponent();

		entt::entity& Get() { return m_Entity; }

	private:
		void set_user_pointer();

	private:
		entt::entity m_Entity;
		Ref<entt::registry> m_Reg;
	};
}

