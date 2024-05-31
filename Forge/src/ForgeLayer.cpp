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

void ForgeLayer::Attach()
{
	std::filesystem::current_path();

	camera.SetPosition({0, 1, 3});
	camera.SetRotation(-90.f, 0.f);

	Input::SetMouseMode(Anvil::MOUSE_MODE_LOCKED);

	cController.SetRotationSpeed(50);
	cController.SetMovementSpeed(2.3f);

	canvas = activeScene->CreateCanvas();
	pos = canvas->AddItem<UI_TEXT>(glm::to_string(camera.position), Vec2(50, 50));
	rot = canvas->AddItem<UI_TEXT>(glm::to_string(camera.rotation), Vec2(50, 65));

	canvas->AddItem<UI_TEXT>("Controls", Vec2(50, 90));
	canvas->AddItem<UI_TEXT>("W-A-S-D : Move along X Z", Vec2(50, 102));
	canvas->AddItem<UI_TEXT>("Q-E : Move along Y", Vec2(50, 114));
	canvas->AddItem<UI_TEXT>("Arrow Keys : look arround", Vec2(50, 126));
	canvas->AddItem<UI_TEXT>("T : Unlock Mouse", Vec2(50, 138));

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

