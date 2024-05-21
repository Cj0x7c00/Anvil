#include "ForgeLayer.h"
#include <filesystem>

ForgeLayer::ForgeLayer(SceneManager& manager, GLFWwindow* win)
	: scManager{ manager }, camera{ scManager.GetActiveScene()->GetActiveCamera()->GetComponent<Camera>() }, Window{win}, AnvilLayer("Forge Editor Layer")
{
	activeScene = scManager.GetActiveScene();
}

void ForgeLayer::Attach()
{
	std::filesystem::current_path();

	camera.SetPosition({ 0.0f, 2.0f, 2.0f });
	glfwSetWindowUserPointer(Window, this);
	glfwSetKeyCallback(Window, keyCallbackWrapper);
}

void ForgeLayer::Update()
{

}

void ForgeLayer::OnGUI()
{
	//SceneViewPannel->Update();
}



void ForgeLayer::Detach()
{

}

void ForgeLayer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_W:
			ANVIL_DEBUG("Key pressed: W");
			camera.Move(glm::vec3(0.0, 0.0, 1.0));
		}
	}
}

void ForgeLayer::setup_menue()
{
	//m_Canvas->AddItem<UI_MENUE>(std::vector<std::string>{ "File", "Edit" });
}
