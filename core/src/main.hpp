#pragma once
#include "window_manager.cpp"
#include "anvRenderer.cpp"
#include "anvPipeline.cpp"
#include "anvSwapChain.cpp"
#include <array>
#include <GLFW/glfw3.h>
#include <memory>

namespace AnvilEngine{

    class AnvilEngineApplication{

        public:
            
            WindowManager WindowManager{800, 600, "Anvil Engine ver 0.0.0"};
            anvRenderer Renderer;
            VkPipelineLayout pipelineLayout;
            std::unique_ptr<anvPipeline> AnvilPipeline;
            std::vector<VkCommandBuffer> CommandBuffers;
            anvSwapChain AnvilSwapChain{anvDevice, WindowManager.GetExtent()};

            

            AnvilEngineApplication()
            {
                ENGINE_INFO("Starting Engine");
                ENGINE_INFO(glfwGetVersionString());
                CreatePipelineLayout();
                CreatePipeline(AnvilSwapChain);
                CreateCommandBuffers();
            }

            anvSwapChain* EngineGetSwapChain()
            {
                return &AnvilSwapChain;
            }


            void CreatePipelineLayout()
            {
                VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
                pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                pipelineLayoutInfo.setLayoutCount = 0;
                pipelineLayoutInfo.pSetLayouts = nullptr;
                pipelineLayoutInfo.pushConstantRangeCount = 0;
                pipelineLayoutInfo.pPushConstantRanges = nullptr;
                if (vkCreatePipelineLayout(anvDevice.m_device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS){
                    ENGINE_ERROR("Failed to create pipeline layout");
                }
            }



            void CreatePipeline(anvSwapChain &swap_chain)
            {
                auto pipelineConfig = anvPipeline::DefaultPipelinecfgInfo(swap_chain.width(), swap_chain.height());
                pipelineConfig.renderPass = swap_chain.getRenderPass();
                pipelineConfig.pipelineLayout = pipelineLayout;
                AnvilPipeline = std::make_unique<anvPipeline>(
                    anvDevice, 
                    "/Users/cj/Desktop/C++ projects/11-12-21/core/src/shaders/sprv.vert", 
                    "/Users/cj/Desktop/C++ projects/11-12-21/core/src/shaders/sprv.frag", 
                    pipelineConfig);
            }



            void CreateCommandBuffers()
            {
                CommandBuffers.resize(AnvilSwapChain.imageCount());

                VkCommandBufferAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocInfo.commandPool = anvDevice.commandPool;
                allocInfo.commandBufferCount = static_cast<uint32_t>(CommandBuffers.size());

                if (vkAllocateCommandBuffers(anvDevice.m_device, &allocInfo, CommandBuffers.data()) != VK_SUCCESS)
                {
                    ENGINE_ERROR("Failed to allocate command buffers");
                }

                for (int i = 0; i < CommandBuffers.size(); i++)
                {
                    VkCommandBufferBeginInfo beginInfo{};
                    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                    if (vkBeginCommandBuffer(CommandBuffers[i], &beginInfo) != VK_SUCCESS)
                    {
                        ENGINE_ERROR("Failed to begin recording command buffer");
                    }

                    VkRenderPassBeginInfo renderPassInfo{};
                    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
                    renderPassInfo.renderPass = AnvilSwapChain.getRenderPass();
                    renderPassInfo.framebuffer = AnvilSwapChain.getFrameBuffer(i);

                    renderPassInfo.renderArea.offset = {0, 0};
                    renderPassInfo.renderArea.extent = AnvilSwapChain.getSwapChainExtent();

                    std::array<VkClearValue, 2> clearValues{};
                    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
                    clearValues[1].depthStencil = {1.0f, 0};
                    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
                    renderPassInfo.pClearValues = clearValues.data();

                    vkCmdBeginRenderPass(CommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

                    AnvilPipeline->Bind(CommandBuffers[i]);
                    vkCmdDraw(CommandBuffers[i], 3, 1, 0, 0);

                    vkCmdEndRenderPass(CommandBuffers[i]);
                    if (vkEndCommandBuffer(CommandBuffers[i]) != VK_SUCCESS)
                    {
                        ENGINE_ERROR("Failed to record command buffer");
                    }
                }
            }
            void DrawFrame()
            {
                uint32_t imgIndex;
                auto result = AnvilSwapChain.acquireNextImage(&imgIndex);

                if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
                {
                    ENGINE_ERROR("Failed to aquire swap chain image");
                }

                result = AnvilSwapChain.submitCommandBuffers(&CommandBuffers[imgIndex], &imgIndex);
                if (result != VK_SUCCESS)
                {
                    ENGINE_ERROR("Failed to present swap chain image");
                }
            }


            void Run(){
                ENGINE_INFO("Running. . .");
                while (!glfwWindowShouldClose(WindowManager.Window)){

                    glfwPollEvents();
                    DrawFrame();
                }
            }

            ~AnvilEngineApplication(){
                ENGINE_INFO("Stopping Engine");
                AnvilPipeline.~unique_ptr();
                vkDestroyPipelineLayout(anvDevice.m_device, pipelineLayout, nullptr);
                Renderer.Clean();
                
                vkDestroySurfaceKHR(anvDevice.m_instance, anvDevice.m_surface, nullptr);
                vkDestroyDevice(anvDevice.m_device, nullptr);
                if (anvDevice.enableValidationLayers){
                    anvDevice.DestroyDebugUtilsMessengerEXT(anvDevice.m_instance, anvDevice.debugMessenger, nullptr);
                }

                // always destroy the instance last
                vkDestroyInstance(anvDevice.m_instance, nullptr);
                glfwDestroyWindow(WindowManager.Window);
                glfwTerminate();
            }

    };

}
