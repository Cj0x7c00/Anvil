#pragma once
#include "window_manager.hpp"
#include "anvGameObject.hpp"
#include "anvRenderer.hpp"
#include "anvLayerStack.hpp"
#include "basic_app.hpp"
//#include "anvImLayer.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <array>
#include <GLFW/glfw3.h>
#include <memory>

namespace AnvilEngine{



    class AnvilEngineApplication{

        public:
            
            WindowManager WindowManager{800, 600, "Anvil Engine ver 0.0.0"};
            AnvDevice anvDevice{WindowManager.Window};
            anvRenderer AnvRenderer{WindowManager, anvDevice};
            std::vector<anvGameObject> GameObjects;
            AnvilLayerStack LayerStack;

            basic_anvApp* BasicApp;

            AnvilEngineApplication();   
            void PushLayer(AnvilLayer* layer);
            void PopLayer(AnvilLayer* layer);
            void Run();
            void LoadGameObjects();

    };

}
