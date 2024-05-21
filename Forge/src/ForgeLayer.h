#pragma once
#include <glm/glm.hpp>
#include "Anvil.hpp"
#include "pannels/SceneView.h"
#include "GLFW/glfw3.h"

class ForgeLayer :
    public Anvil::AnvilLayer
{
public:

    ForgeLayer(SceneManager& manager, GLFWwindow*  win);

    void Attach() override;
    void Update() override;
    void OnGUI()  override;
    void Detach() override;

    /// TEMP
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    // Static function to act as a trampoline
    static void keyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
        ANVIL_DEBUG("Key Callback");
        ForgeLayer* layer = static_cast<ForgeLayer*>(glfwGetWindowUserPointer(window));
        if (layer) {
            layer->keyCallback(window, key, scancode, action, mods);
        }
    }
private:
    void setup_menue();

private:
    SceneManager& scManager;
    SCENE activeScene;
    Anvil::Camera& camera;
    GLFWwindow* Window;
};

