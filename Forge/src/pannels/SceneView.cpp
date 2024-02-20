#include "SceneView.h"
#include <core/src/Scene/Components.h>

void SceneView::Init()
{
	m_activeScene = m_SceneManager.GetActiveScene();

	DrawUI();
}

void SceneView::DrawEntities()
{
	auto& Reg = m_activeScene->GetRegistry();
	auto& View = Reg.view<TagComponent>();

	View.each([&](TagComponent& tag) {
		m_Canvas->DrawElement<UI_Text>(tag.Get().c_str());
	});
}

void SceneView::DrawUI()
{
	m_Canvas->AddItem<UI_RECT>("Scene View", Vec2{ 400, 600 }, Vec2{ 0, 0 }, [&]() { DrawEntities(); });
}
