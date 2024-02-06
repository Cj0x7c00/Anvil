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
        windowFlags |= ImGuiWindowFlags_NoTitleBar;
        windowFlags |= ImGuiWindowFlags_NoResize;
        windowFlags |= ImGuiWindowFlags_NoMove;

        //ImGuiIO& io = ImGui::GetIO();

        //
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        ImGui::Begin("##Canvas", 0, windowFlags);
        
        auto view = m_CanvasItems.view<Button>();

        view.each([](Button& item) {
            item.Draw();
        });

        ImGui::End();
    }

    CanvasItem& Canvas::AddButton(const char* label, Vec2 size, Vec2 position, std::function<void()> FnCmd)
    {
        auto ent = m_CanvasItems.create();
        auto btn = m_CanvasItems.emplace<Button>(ent, label, size, position, FnCmd);
        return btn;
    }
}
