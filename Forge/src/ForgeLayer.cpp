#include "ForgeLayer.h"
#include <filesystem>
#include <glm/gtx/string_cast.hpp>

ForgeLayer::ForgeLayer(SceneManager& manager)
	: scManager{ manager },
	camera{ scManager.GetActiveScene()->GetActiveCamera()->GetComponent<Camera>() }, 
	cController{camera},
	AnvilLayer("Forge Editor Layer")

{
	activeScene = scManager.GetActiveScene();
}

void CreateEntity()
{
	static int move_pos = 1;

	auto& Entity = Anvil::SceneManager::GetActiveScene()->CreateEntity("New Entity" + std::to_string(move_pos), 
		{move_pos, move_pos, move_pos}, {0, 0, 0}, {1, 1, 1});

	Entity->AddComponent<SpriteComponent>();

	move_pos++;
}

void ForgeLayer::Attach()
{
	//std::filesystem::current_path();

	Quad1 = activeScene->CreateEntity("Quad1", glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1.f });
	Quad1->AddComponent<Anvil::SpriteComponent>();

	Quad2 = activeScene->CreateEntity("Quad2", glm::vec3{ 1, 1, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 4.f });
	Quad2->AddComponent<Anvil::SpriteComponent>();

	camera.SetPosition({0, 1, 3});
	camera.SetRotation(-90.f, 0.f);

	Input::SetMouseMode(Anvil::MOUSE_MODE_LOCKED);

	cController.SetRotationSpeed(50);
	cController.SetMovementSpeed(2.3f);

	canvas = activeScene->CreateCanvas();

	canvas->AddItem<Anvil::UI_Window>("New Entity")->DrawElement<UI_BUTTON>("CreateEntity", Vec2(0, 0), Vec2(70, 20), CreateEntity);
	canvas->AddItem<UI_TEXT>("Position", Vec2(50, 35));
	pos = canvas->AddItem<UI_TEXT>(glm::to_string(camera.position), Vec2(50, 50));
	canvas->AddItem<UI_TEXT>("Rotation", Vec2(50, 65));
	rot = canvas->AddItem<UI_TEXT>(glm::to_string(camera.rotation), Vec2(50, 80));

	canvas->AddItem<UI_TEXT>("Controls", Vec2(50, 110));
	canvas->AddItem<UI_TEXT>("W-A-S-D : Move along X Z", Vec2(50, 125));
	canvas->AddItem<UI_TEXT>("Q-E : Move along Y", Vec2(50, 140));
	canvas->AddItem<UI_TEXT>("T : Unlock Mouse", Vec2(50, 155));
	canvas->AddItem<UI_TEXT>("Arrow Keys : look arround", Vec2(50, 170));

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

	pos->text = glm::to_string(camera.position);
	rot->text = glm::to_string(camera.rotation);
}

void ForgeLayer::OnGUI()
{
}



void ForgeLayer::Detach()
{

}

