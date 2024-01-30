#include "ForgeLayer.h"

ForgeLayer::ForgeLayer() 
	: AnvilLayer("Forge Editor Layer")
{
	m_Scene = Anvil::Scene::Create("Main Scene");
}

void ForgeLayer::Attach()
{
	Anvil::ANVIL_INFO("Attach");

	auto Triangle = m_Scene->CreateEntity("Triangle");

	std::vector<Anvil::vertex> verts =
	{
		{{0.0, -0.5}, {1.0, 0.0, 0.0}},
		{{0.5, 0.5}, {0.0, 1.0, 0.0}},
		{{-0.5, -0.5}, {0.0, 0.0, 1.0}}
	};

	auto Sprite = Triangle->AddComponent<Anvil::SpriteComponent>(verts);
}

void ForgeLayer::Update()
{
	Anvil::ANVIL_INFO("Update");
}

void ForgeLayer::Detach()
{
	Anvil::ANVIL_INFO("Detach");
}
