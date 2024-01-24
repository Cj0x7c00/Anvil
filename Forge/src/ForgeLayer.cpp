#include "ForgeLayer.h"

ForgeLayer::ForgeLayer() 
	: AnvilLayer("Forge Editor Layer")
{
	ANVIL_ASSERT(true && "Assert msg");
}

void ForgeLayer::Attach()
{
	Anvil::ANVIL_INFO("Attach");
}

void ForgeLayer::Update()
{
	Anvil::ANVIL_INFO("Update");
}

void ForgeLayer::Detach()
{
	Anvil::ANVIL_INFO("Detach");
}
