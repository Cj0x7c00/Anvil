#pragma once
#include "window_manager.hpp"
#include "anvGameObject.hpp"
#include "anvRenderer.hpp"
#include "anvLayerStack.hpp"
//#include "anvImLayer.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <array>
#include <GLFW/glfw3.h>
#include <memory>
#include "anvTimeStep.hpp"

namespace Anvil{

    class AnvilApplication{

        public:
            
            WindowManager WindowManager{800, 600, "Anvil Engine ver 0.0.0"};
            AnvDevice anvDevice{WindowManager.Window};
            anvRenderer AnvRenderer{WindowManager, anvDevice};
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
