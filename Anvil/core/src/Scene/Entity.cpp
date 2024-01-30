#include "Entity.h"
#include <Util/anvLog.hpp>

namespace Anvil
{
	template<typename Component, typename... Args>
	void Entity::AddComponent(Args&&... args)
	{
		m_Reg.emplace<Component>(m_Entity, std::forward<Args>(args)...);
	}

	template<typename Component>
	void Entity::RemoveComponent()
	{
		m_Reg.remove<Component>(m_Entity);
	}

	Entity::Entity(entt::registry& _reg, std::string _name)
		: m_Reg{ _reg }
	{
		m_Entity = m_Reg.create();

		AddComponent<TagComponent>(_name);
		AddComponent<UUIDComponent>();
		set_user_pointer();

		ENGINE_INFO("Created Entity: {}", _name);
	}

	void Entity::set_user_pointer()
	{
		m_Reg.emplace<UserPointerComponent>(m_Entity, this);
	}
}