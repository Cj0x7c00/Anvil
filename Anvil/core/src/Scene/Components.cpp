#include "Entity.h"

namespace Anvil
{
	UserPointerComponent::UserPointerComponent(Entity* _ent)
		: entity{ _ent }
	{

	}

	Entity* UserPointerComponent::Get()
	{
		return entity;
	}
}