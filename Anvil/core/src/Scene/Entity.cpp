#include "Entity.h"

namespace Anvil
{
	template<typename Component, typename... Args>
	void Entity::AddComponent(Args&&... args)
	{
		m_Reg->emplace_or_replace<Component>(m_Entity, std::forward<Args>(args)...);
	}

	template<typename Component>
	void Entity::RemoveComponent()
	{
		m_Reg->remove<Component>(m_Entity);
	}

	void Entity::set_user_pointer()
	{
		m_Reg->emplace_or_replace<UserPointerComponent>(m_Entity, this);
	}
}