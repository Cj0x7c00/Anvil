#include "Forge.h"
#include <core/src/Scene/Components.h>

void Forge::Awake() 
{

	Scene = m_SceneManager.GetActiveScene();
	Quad = Scene->CreateEntity("Sprite", glm::vec3{ 0.5f, 1.0f, 1.0f }, glm::vec3{0, 0, 0}, glm::vec3{1.f});
	Quad2 = Scene->CreateEntity("Sprite2", glm::vec3{ 0.f, 0.f, 0.f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1.f });
	Quad3 = Scene->CreateEntity("Sprite3", glm::vec3{ 1.f, 1.f, 1.f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1.f });

	//AddComponent<SpriteComponent>(Texture text)
	auto Sprite = Quad->AddComponent<Anvil::SpriteComponent>();
	auto Sprite2 = Quad2->AddComponent<Anvil::SpriteComponent>();
	auto Sprite3 = Quad3->AddComponent<Anvil::SpriteComponent>();

	PushLayer(new ForgeLayer(m_SceneManager));
}

void Forge::Update()
{

}