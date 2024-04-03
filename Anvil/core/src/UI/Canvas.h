#pragma once

#include "CanvasItems.h"
#include "entt/entt.hpp"
#include <functional>
#include "../Base/macros.hpp"
#include "../Base/Pointer.hpp"

struct ImVec2;

namespace Anvil
{
	class ANV_API Canvas
	{
	public:
		static Ref<Canvas> Create();

		void Update();

		
		template<typename CItem, typename... Args>
		Ref<CItem> AddItem(Args&&... args) {
			// Construct the derived item and add it to the vector
			std::shared_ptr<CItem> item = std::make_shared<CItem>(std::forward<Args>(args)...);
			m_Items.push_back(item);

			// Return a reference to the newly added item
			return item;
		}

		template<typename CItem, typename... Args>
		Ref<CItem> DrawElement(Args&&... args) {
			// Construct the derived item and add it to the vector
			std::shared_ptr<CItem> item = std::make_shared<CItem>(std::forward<Args>(args)...);
			item->Draw();
			return item;
		}

	private:
		/*entt::registry m_Reg;*/
		std::vector<Ref<CanvasItem>> m_Items = {};
	};
}
