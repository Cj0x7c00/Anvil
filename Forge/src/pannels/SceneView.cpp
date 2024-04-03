#include "SceneView.h"
#include <core/src/Scene/Components.h>

void SceneView::Update()
{
	static auto EntityView  = m_Canvas->AddItem<UI_Window>("Entity View");
	static auto FileView = m_Canvas->AddItem<UI_Window>("File View");
	static auto SceneView = m_Canvas->AddItem<UI_Window>("Scene View");

	auto& Reg = m_activeScene->GetRegistry();
	auto& View = Reg.view<TagComponent>();

	ANV_CALL_ONCE([&]() {
		View.each([&](TagComponent& tag) {
			SceneView->DrawElement<UI_Selectable>(tag.Get().c_str());
		});
	});
}

void SceneView::Init()
{
	m_activeScene = m_SceneManager.GetActiveScene();

	InitUI();
}


void SceneView::InitUI()
{

	//auto& Reg = m_activeScene->GetRegistry();
	//auto& View = Reg.view<TagComponent>();

	//View.each([&](TagComponent& tag) {
	//	window->DrawElement<UI_Selectable>(tag.Get().c_str());
	//});

	//window->DrawElement<UI_Selectable>("Hello");

}
