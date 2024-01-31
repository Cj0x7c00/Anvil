#include "Forge.h"
#include <core/src/Scene/Components.h>

void Forge::Awake() 
{
	Scene = m_SceneManager.GetActiveScene();

	Triangle1 = Scene->CreateEntity("Triangle");
	Triangle2 = Scene->CreateEntity("Triangle2");

	std::vector<Anvil::vertex> verts =
	{
		{{0.0, -0.5}, {1.0, 0.0, 0.0}},
		{{0.5, 0.5}, {0.0, 1.0, 0.0}},
		{{-0.5, 0.5}, {0.0, 0.0, 1.0}}
	};

	std::vector<Anvil::vertex> verts2 =
	{
		{{0.1, -0.2}, {1.6, 0.0, 0.0}},
		{{0.6, 0.2}, {0.4, 1.0, 0.0}},
		{{-0.6, 0.2}, {0.2, 0.6, 1.0}}
	};

	auto Sprite = Triangle1->AddComponent<Anvil::SpriteComponent>(verts);
	auto Sprite2 = Triangle2->AddComponent<Anvil::SpriteComponent>(verts2);
}