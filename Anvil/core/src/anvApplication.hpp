#pragma once
#include "./Window/Window.hpp"
#include "./Vulkan/anvRenderer.hpp"
#include "./Layer/anvLayerStack.hpp"
#include "./Util/Time/anvTimeStep.hpp"
#include "anvGameObject.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/constants.hpp"

#include <array>
#include "GLFW/glfw3.h"
#include <memory>

namespace Anvil{

    class AnvilApplication{

        public:
            
            Ref<Window>    m_Window;
            Ref<AnvDevice> anvDevice;
            anvRenderer*    AnvRenderer = nullptr;
            std::vector<anvGameObject> GameObjects;
            AnvilLayerStack LayerStack;
            float LastFrame = 0.0f;

            AnvilApplication();   
            void PushLayer(AnvilLayer* layer);
            void PopLayer(AnvilLayer* layer);
            virtual void Run();
            void LoadGameObjects();

    };
    
    AnvilApplication* CreateApplication();
}
