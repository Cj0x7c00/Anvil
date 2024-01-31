#include "Forge.h"
#include <core/src/Scene/Components.h>

void Forge::Awake() 
{
	Scene = m_SceneManager.GetActiveScene();

	Triangle1 = Scene->CreateEntity("Triangle");
	Background = Scene->CreateEntity("Background");

	const std::vector<Anvil::vertex> vertices = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	const std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
	};

	const std::vector<Anvil::vertex> vertices2 = {
	{{-1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
	{{1.0f, -1.0f}, {0.0f, 1.0f, 0.04f}},
	{{1.0f, 1.0f}, {0.6f, 0.0f, 0.0f}},
	{{-1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}}
	};

	const std::vector<uint16_t> indices2 = {
	0, 1, 2, 2, 3, 0
	};

	auto Sprite = Triangle1->AddComponent<Anvil::SpriteComponent>(vertices, indices);
	auto Sprite2 = Background->AddComponent<Anvil::SpriteComponent>(vertices2, indices2);
}

void Forge::Update()
{

}