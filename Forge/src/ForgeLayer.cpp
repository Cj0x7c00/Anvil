#include "ForgeLayer.h"
#include <filesystem>
#include <glm/gtx/string_cast.hpp>

SCENE ForgeLayer::activeScene = nullptr;
ENTITY ForgeLayer::Quad1 = nullptr;
ENTITY ForgeLayer::Quad2 = nullptr;

ForgeLayer::ForgeLayer(SceneManager& manager)
	: scManager{ manager },
	camera{ scManager.GetActiveScene()->GetActiveCamera()->GetComponent<Camera>() }, 
	cController{camera},
	AnvilLayer("Forge Editor Layer")

{
	activeScene = scManager.GetActiveScene();
}

void ForgeLayer::CreateSprite()
{
	static int count = 1;

	ENTITY newEntity = activeScene->CreateEntity("Sprite" + std::to_string(count), glm::vec3(count/2, .5, count/2), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
	newEntity->AddComponent<Anvil::SpriteComponent>();
	auto name = newEntity->GetComponent<Anvil::TagComponent>().Get();
		
	ANVIL_INFO("Creating sprite: {}", name);

	++count;
}

void ForgeLayer::Attach()
{
	//std::filesystem::current_path();

	canvas = activeScene->CreateCanvas();


	Quad1 = activeScene->CreateEntity("Quad1", glm::vec3{ 0, 0, 0 }, glm::vec3{ 90.f, 0.f, 0.f }, glm::vec3{ 7.f });
	Quad1->AddComponent<Anvil::SpriteComponent>(glm::vec3{ 0.902, 0.878, 0.733 });

	Quad2 = activeScene->CreateEntity("Quad2", glm::vec3{ 1, 3, 1 }, glm::vec3{ 0 }, glm::vec3{ 1.f });
	Quad2->AddComponent<Anvil::SpriteComponent>(glm::vec3{ 1, 0.294, 0 });

	camera.SetPosition({0, 1, 3});
	camera.SetRotation(-90.f, 0.f);

	Input::SetMouseMode(Anvil::MOUSE_MODE_LOCKED);

	cController.SetRotationSpeed(50);
	cController.SetMovementSpeed(2.3f);

	canvas->AddItem<UI_TEXT>("Position", Vec2(50, 35));
	pos = canvas->AddItem<UI_TEXT>(glm::to_string(camera.position), Vec2(50, 50));
	canvas->AddItem<UI_TEXT>("Rotation", Vec2(50, 65));
	rot = canvas->AddItem<UI_TEXT>(glm::to_string(camera.rotation), Vec2(50, 80));

	canvas->AddItem<UI_TEXT>("Controls", Vec2(50, 110));
	canvas->AddItem<UI_TEXT>("W-A-S-D : Move along X Z", Vec2(50, 125));
	canvas->AddItem<UI_TEXT>("Q-E : Move along Y", Vec2(50, 140));
	canvas->AddItem<UI_TEXT>("T : Unlock Mouse", Vec2(50, 155));
	canvas->AddItem<UI_TEXT>("SPACE : Move Faster", Vec2(50, 170));
	canvas->AddItem<UI_TEXT>("B : Create New Entity", Vec2(50, 185));
	canvas->AddItem<UI_TEXT>("Arrow Keys : look arround", Vec2(50, 200));

	auto w = canvas->AddItem<UI_WINDOW>("Window", Vec2(20, 40), Vec2(0, 0));

	w->DrawElement<UI_BUTTON>("Create Entity", Vec2(100, 20), Vec2(50, 190), CreateSprite);
}

void ForgeLayer::Update()
{
	auto delta = Time::DeltaTime();
	cController.ProcessKeyboard(delta);

	//auto [x, y] = Input::GetMousePos();

	// release mouse 
	if (Input::IsKeyPressed(ANV_KEY_T))
	{
		Input::SetMouseMode(MOUSE_MODE_FREE);
	}

	if (Input::IsKeyPressed(ANV_KEY_B))
	{
		CreateSprite();
	}

	pos->text = glm::to_string(camera.position);
	rot->text = glm::to_string(camera.rotation);

}

void ForgeLayer::OnGUI()
{
}



void ForgeLayer::Detach()
{

}

