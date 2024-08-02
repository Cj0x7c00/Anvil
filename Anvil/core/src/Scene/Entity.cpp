#include "Entity.h"
#include "Components.h"
#include <Util/anvLog.hpp>

namespace Anvil
{
	//template <typename Component, typename... Args>
	//Component& Entity::AddComponent(Args&&... args)
	//{
	//	return m_Reg.emplace<Component>(m_Entity, std::forward<Args>(args)...);
	//}

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
		auto t = AddComponent<TransformComponent>();
		AddComponent<UUIDComponent>();

		set_user_pointer();

		ENGINE_INFO("Created Entity: {} At position ({}, {}, {})", _name, t.position.x, t.position.y, t.position.z);
	}

	Entity::Entity(entt::registry& _reg, std::string _name, glm::vec3 position, glm::vec3  rotation, glm::vec3 scale)
		: m_Reg{ _reg }
	{
		m_Entity = m_Reg.create();

		AddComponent<TagComponent>(_name);
		auto t = AddComponent<TransformComponent>(position, rotation, scale);
		AddComponent<UUIDComponent>();

		set_user_pointer();

		ENGINE_INFO("Created Entity: {} At position ({}, {}, {})", _name, t.position.x, t.position.y, t.position.z);
	}

	void Entity::set_user_pointer()
	{
		// tie an Entt entity to an Anvil entity
		m_Reg.emplace<UserPointerComponent>(m_Entity, this);
	}
}