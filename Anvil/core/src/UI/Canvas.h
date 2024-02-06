#pragma once

#include "CanvasItems.h"
#include "../Base/macros.hpp"
#include "../Base/Pointer.hpp"
#include "entt/entt.hpp"
#include <functional>

struct ImVec2;

namespace Anvil
{
	class ANV_API Canvas
	{
	public:
		static Ref<Canvas> Create();

		void Update();

		CanvasItem& AddButton(const char* label, Vec2 size= Vec2(0, 0), Vec2 position= Vec2(0, 0), std::function<void()> FnCmd = nullptr);
	private:
		entt::registry m_CanvasItems;
	};
}
