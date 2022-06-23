#pragma once
#include "window_manager.hpp"
#include "anvGameObject.hpp"
#include "anvRenderer.hpp"
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

            AnvilEngineApplication();   


            void Run();
            void LoadGameObjects();

    };

}
