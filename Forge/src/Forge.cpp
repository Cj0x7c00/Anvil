#include "Forge.h"
#include "imgui/imgui.h"
#include <core/src/Scene/Components.h>



void Forge::Awake() 
{

	Scene = m_SceneManager.GetActiveScene();
	auto Canvas = Scene->CreateCanvas();

	Canvas->AddButton("Click Me!", { 0, 0 }, { 20, 40 }, []() { ANVIL_INFO("Clicked!"); });

	Triangle1 = Scene->CreateEntity("Triangle");



	const std::vector<Anvil::vertex> vertices = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
	};

	auto Sprite = Triangle1->AddComponent<Anvil::SpriteComponent>(vertices, indices);

}

void Forge::Update()
{

}