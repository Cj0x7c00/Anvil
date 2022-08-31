#pragma once
#include "anvPipeline.hpp"
#include "anvGameObject.hpp"
#include "anvDevice.hpp"

#include <array>
#include <memory>
#include "anvTimeStep.hpp"

namespace Anvil{



    class SimpleRenderSystem{

        public:
            AnvDevice& anvDevice;

            VkPipelineLayout pipelineLayout;
            std::unique_ptr<anvPipeline> AnvilPipeline;


            SimpleRenderSystem(AnvDevice& device, VkRenderPass renderPass);  
            ~SimpleRenderSystem(){ 
                vkDeviceWaitIdle(anvDevice.m_device); //
                vkDestroyPipelineLayout(anvDevice.m_device, pipelineLayout, nullptr); 
                }

            SimpleRenderSystem(const SimpleRenderSystem &) = delete;
            SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

            void CreatePipelineLayout();
            void CreatePipeline(VkRenderPass renderPass);
            void RenderGameObjects(VkCommandBuffer cmdbuffer, std::vector<anvGameObject> &GameObjects, Timestep ts);
    };

}
