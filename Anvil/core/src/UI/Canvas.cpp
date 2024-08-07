#include "Canvas.h"
#include "imgui.h"
#include "Util/anvLog.hpp"


namespace Anvil
{
    Ref<Canvas> Canvas::Create()
    {
        return CreateRef<Canvas>();
    }

    void Canvas::Update()
    {
        static ImGuiWindowFlags windowFlags = 0;
        windowFlags |= ImGuiWindowFlags_NoBackground;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        windowFlags |= ImGuiWindowFlags_NoTitleBar;
        windowFlags |= ImGuiWindowFlags_NoResize;
        windowFlags |= ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoDocking;

        // TODO: add condition for this, should not display if no menue items are being drawn
        windowFlags |= ImGuiWindowFlags_MenuBar;

       

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        ImGui::Begin("##Canvas", 0, windowFlags);
        ImGui::DockSpace(ImGui::GetID("##Canvas"), ImVec2(), ImGuiDockNodeFlags_PassthruCentralNode);
        
        for (auto& item : m_Items)
        {
            item->Draw();
        }
       
        ImGui::End();

        //ImGui::ShowStyleEditor();
    }
    

}
