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
	Quad = Scene->CreateEntity("Triangle");

	PushLayer(new ForgeLayer(m_SceneManager, Canvas));

	//AddComponent<SpriteComponent>(Texture text)
	auto Sprite = Quad->AddComponent<Anvil::SpriteComponent>();

}

void Forge::Update()
{

}