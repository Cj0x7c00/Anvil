#include "ForgeLayer.h"

ForgeLayer::ForgeLayer(SceneManager& manager, Ref<Canvas> canvas)
	: scManager{ manager }, m_Canvas{canvas}, AnvilLayer("Forge Editor Layer")
{
	SceneViewPannel = new SceneView(scManager, m_Canvas);
}

void ForgeLayer::Attach()
{
	
}

void ForgeLayer::Update()
{

}

void ForgeLayer::Detach()
{

}
