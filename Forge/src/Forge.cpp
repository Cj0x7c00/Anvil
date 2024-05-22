#include "Forge.h"
#include <core/src/Scene/Components.h>

void Forge::Awake() 
{

	Scene = m_SceneManager.GetActiveScene();
	auto Canvas = Scene->CreateCanvas();
	Quad = Scene->CreateEntity("Triangle");

	PushLayer(new ForgeLayer(m_SceneManager));

	//AddComponent<SpriteComponent>(Texture text)
	auto Sprite = Quad->AddComponent<Anvil::SpriteComponent>();

}

void Forge::Update()
{

}