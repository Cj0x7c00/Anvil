#include "ForgeLayer.h"
#include <filesystem>

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

	camera.SetPosition({0, 2, 1});

	Input::SetMouseMode(Anvil::MOUSE_MODE_LOCKED);
	
	cController.SetMouseSensitivity(1);
	cController.SetMovementSpeed(0.3f);
}

void ForgeLayer::Update()
{
	cController.ProcessKeyboard(Time::DeltaTime());

	auto [x, y] = Input::GetMousePos();

	cController.ProcessMouseMovement(x, y, false);

	if (Input::IsKeyPressed(ANV_KEY_T))
	{
		Input::SetMouseMode(MOUSE_MODE_FREE);
	}
}

void ForgeLayer::OnGUI()
{
}



void ForgeLayer::Detach()
{

}

