#include "CanvasItems.h"
#include "imgui/imgui.h"

namespace Anvil
{
	void Button::Draw()
	{
		ImGui::SetCursorPos(ImVec2(position.x, position.y));
		if (ImGui::Button(label, ImVec2(size.x, size.y)))
		{
			if (Fn != nullptr)
			{
				Fn();
			}
		}
	}
}