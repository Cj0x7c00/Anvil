#include "CanvasItems.h"
#include "imgui/imgui.h"

namespace Anvil
{

	std::string UI_Button::item = "Button";
	std::string UI_Rect::item   = "Rect";
	std::string UI_Text::item   = "Text";

	void UI_Button::Draw()
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

	void UI_Rect::Draw()
	{
		static ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
		ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + position.x, viewport->WorkPos.y + position.y));

		ImGui::Begin(name, 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | 
			ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | 
			ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking  |
			ImGuiWindowFlags_::ImGuiWindowFlags_ChildWindow);

		// Draw Inner Elements
		(InnerElements == nullptr) ? NULL : InnerElements();

		ImGui::EndChild();
	}


	void UI_Text::Draw()
	{
		ImGui::Text(text);
	}
}