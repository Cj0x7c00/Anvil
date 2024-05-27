#include "Forge.h"
#include <core/src/Scene/Components.h>

void Forge::Awake() 
{

	Scene = m_SceneManager.GetActiveScene();
	auto Canvas = Scene->CreateCanvas();
	Quad = Scene->CreateEntity("Sprite");
	Quad2 = Scene->CreateEntity("Sprite2");
	Quad3 = Scene->CreateEntity("Sprite3");

	PushLayer(new ForgeLayer(m_SceneManager));

	//AddComponent<SpriteComponent>(Texture text)
	//auto Sprite = Quad->AddComponent<Anvil::SpriteComponent>();
	//Quad->GetComponent<TransformComponent>().position = glm::vec3{ 0.5f, 1.0f, 1.0f };

	auto Sprite2 = Quad2->AddComponent<Anvil::SpriteComponent>();
	Quad2->GetComponent<TransformComponent>().position = glm::vec3{ 0.f, 0.f, 0.f };

	//auto Sprite3 = Quad3->AddComponent<Anvil::SpriteComponent>();
	//Quad3->GetComponent<TransformComponent>().position = glm::vec3{ 1.f, 1.f, 1.f };
}

void Forge::Update()
{

}