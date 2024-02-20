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

       

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        ImGui::Begin("##Canvas", 0, windowFlags);
        
        for (auto& item : m_Items)
        {
            item->Draw();
        }
       
        ImGui::DockSpace(ImGui::GetID("##Canvas"), ImVec2(), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::End();
    }
    

}
