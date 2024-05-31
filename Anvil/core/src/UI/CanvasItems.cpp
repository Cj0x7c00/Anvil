#include "CanvasItems.h"
#include "imgui/imgui.h"
#include <Util/anvLog.hpp>

namespace Anvil
{

	std::string UI_Menue::item  = "Menue";
	std::string UI_Button::item = "Button";
	std::string UI_Window::item = "Window";
	std::string UI_Selectable::item = "Selectable";
	std::string UI_Text::item = "Text";

	void UI_Button::Draw()
	{
		if (position != Vec2(0, 0))
		ImGui::SetCursorPos(ImVec2(position.x, position.y));
		if (ImGui::Button(label.c_str(), ImVec2(size.x, size.y)))
		{
			if (Fn != nullptr)
			{
				Fn();
			}
		}
	}

	void UI_Window::Draw()
	{
		//static ImGuiViewport* viewport = ImGui::GetMainViewport();

		//ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
		//ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x + position.x, viewport->Pos.y + position.y));		

		ImGui::Begin(name.c_str());
	
		for (auto& el : InnerElements)
		{
			el->Draw();
		}

		ImGui::End();
	}


	UI_Selectable::UI_Selectable(std::string Text="##")
		: text{ Text }, CanvasItem(item)
	{
		
	}

	void UI_Selectable::Draw()
	{
		if (text == "" || text == " ")
		{
			ImGui::Selectable("##", &selected);
		}
		else {
			ImGui::Selectable(text.c_str(), &selected);
		}

		if (selected)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
			ImGui::Button("No");
			ImGui::PopStyleColor();
		}

	}

	void UI_Menue::Draw()
	{
		if(ImGui::BeginMenuBar())
		{
			for (auto& item : menueItems)
			{
				if (ImGui::BeginMenu(item.c_str()))
				{
					if (ImGui::MenuItem(item.c_str()))
					{

					}

					ImGui::EndMenu();
				}
			}

			ImGui::EndMenuBar();
		}
	}


	void UI_Text::Draw()
	{
		ImGui::SetCursorPos(ImVec2(position.x, position.y));
		ImGui::Text(text.c_str());
	}
}