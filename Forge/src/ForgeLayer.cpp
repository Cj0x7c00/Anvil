#include "ForgeLayer.h"
#include <filesystem>

ForgeLayer::ForgeLayer(SceneManager& manager)
	: scManager{ manager },
	camera{ scManager.GetActiveScene()->GetActiveCamera()->GetComponent<Camera>() }, 
	AnvilLayer("Forge Editor Layer")
{
	activeScene = scManager.GetActiveScene();
}

void ForgeLayer::Attach()
{
	std::filesystem::current_path();

	camera.SetPosition({ 0.0f, 2.f, 2.f });
}

void ForgeLayer::Update()
{
	if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		camera.Move({0.f, -0.01f, 0.f});
	}
	if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		camera.Move({ 0.f, 0.01f, 0.f });
	}
	if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		camera.Move({ 0.01f, 0.f, 0.f });
	}
	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		camera.Move({ -0.01f, 0.f, 0.f });
	}

	if (Input::IsKeyPressed(GLFW_KEY_UP))
	{
		camera.Move({ 0.f, 0.f,  0.01f });
	}
	if (Input::IsKeyPressed(GLFW_KEY_DOWN))
	{
		camera.Move({ 0.f, 0.f,  -0.01f });
	}

	static int rotation = 0;
	if (Input::IsKeyPressed(GLFW_KEY_LEFT))
	{
		camera.SetRotation(0.f, rotation++);
	}
	if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
	{
		camera.SetRotation(0.f, rotation--);
	}
}

void ForgeLayer::OnGUI()
{
}



void ForgeLayer::Detach()
{

}

