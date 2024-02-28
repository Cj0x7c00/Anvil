#include "ForgeLayer.h"
#include <filesystem>

ForgeLayer::ForgeLayer(SceneManager& manager, Ref<Canvas> canvas)
	: scManager{ manager }, m_Canvas{canvas}, AnvilLayer("Forge Editor Layer")
{
	setup_menue();
	SceneViewPannel = new SceneView(scManager, m_Canvas);
}

void ForgeLayer::Attach()
{
	std::filesystem::current_path();
}

void ForgeLayer::Update()
{

}

void ForgeLayer::OnGUI()
{
	SceneViewPannel->Update();
}



void ForgeLayer::Detach()
{

}

void ForgeLayer::setup_menue()
{
	m_Canvas->AddItem<UI_MENUE>(std::vector<std::string>{ "File", "Edit" });
}
