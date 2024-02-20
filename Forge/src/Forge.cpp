#include "Forge.h"
#include <core/src/Scene/Components.h>

void MyCustomFunc()
{
	static int clicks;
	ANVIL_WARN("My Function clicks: {}", clicks);
	clicks++;
}

void Forge::Awake() 
{

	Scene = m_SceneManager.GetActiveScene();
	auto Canvas = Scene->CreateCanvas();

	PushLayer(new ForgeLayer(m_SceneManager, Canvas));
	


	Triangle1 = Scene->CreateEntity("Triangle");

	static ENTITY MyEntity = Scene->CreateEntity("MyEntity");
	static ENTITY MyEntity2 = Scene->CreateEntity("MyEntity1");
	static ENTITY MyEntity3 = Scene->CreateEntity("MyEntity2");
	static ENTITY MyEntity4 = Scene->CreateEntity("MyEntity3");
	static ENTITY MyEntity5 = Scene->CreateEntity("MyEntity4");
	static ENTITY MyEntity6 = Scene->CreateEntity("MyEntity5");
	static ENTITY MyEntity7 = Scene->CreateEntity("MyEntity6");


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