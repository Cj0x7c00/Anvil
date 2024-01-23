#pragma once
#include "../Base/Pointer.hpp"

namespace Anvil
{
	class RenderSystem
	{
	public:
		static Ref<RenderSystem> Default();

		virtual void Init() = 0;
		virtual void NewFrame() = 0;
	};
}