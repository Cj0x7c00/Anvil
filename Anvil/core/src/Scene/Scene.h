#pragma once
#include "../Base/Pointer.hpp"

namespace Anvil
{
	class Entity;

	class Scene
	{
	public:
		static Ref<Scene> Create();

		Ref<Entity> CreateEntity();

	private:

		friend class Entity;
	};
}
