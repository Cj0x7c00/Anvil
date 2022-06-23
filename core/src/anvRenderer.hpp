#pragma once
#include "window_manager.hpp"
#include "anvSwapChain.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <array>
#include <GLFW/glfw3.h>
#include <memory>
#include <cassert>

namespace AnvilEngine{


    class anvRenderer{

        public:

            anvRenderer(WindowManager &Window, AnvDevice& device);
            ~anvRenderer();

            anvRenderer(const anvRenderer &) = delete;
            anvRenderer &operator=(const anvRenderer &) = delete; 

            VkRenderPass getSwapChainRenderPass() const {return AnvilSwapChain->getRenderPass();}
            bool isFrameInProgress() const {return isFrameStarted;}
            VkCommandBuffer getCurrentCommandBuffer() {
                assert(isFrameStarted && "Cannot get command buffer when frame is in progress");
                return CommandBuffers[currentFrameIndex];
            }

            VkCommandBuffer BeginFrame();
            void EndFrame();
            void BeginSwapChainRenderPass(VkCommandBuffer commandBuffer);
            void EndSwapChainRenderPass(VkCommandBuffer commandBuffer);

            void RecreateSwapChain();
            void CreateCommandBuffers();
            void FreeCommandBuffers();

            int getFrameIndex() const
            {
                ENGINE_ASSERT(isFrameStarted && "Cannot get frame index when frame is in progress ");
                return currentFrameIndex; 
            }

            WindowManager& Window;
            AnvDevice& anvDevice;
            std::vector<VkCommandBuffer> CommandBuffers;
            std::unique_ptr<anvSwapChain> AnvilSwapChain;

            uint32_t currentImageIndex;
            int currentFrameIndex = 0; 
            bool isFrameStarted  = false;

    };

}