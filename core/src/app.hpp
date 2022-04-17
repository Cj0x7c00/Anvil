#pragma once
#include "window_manager.hpp"
#include "anvPipeline.hpp"
#include "anvSwapChain.hpp"
#include "anvModel.hpp"
//#include "anvImLayer.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <array>
#include <GLFW/glfw3.h>
#include <memory>

namespace AnvilEngine{

    struct PushConstantData
    {
        glm::vec2 offset;
        alignas(16) glm::vec3 color;
    };

    class AnvilEngineApplication{

        public:
            
            WindowManager WindowManager{800, 600, "Anvil Engine ver 0.0.0"};
            AnvDevice anvDevice{WindowManager.Window};
            VkPipelineLayout pipelineLayout;
            std::unique_ptr<anvPipeline> AnvilPipeline;
            std::vector<VkCommandBuffer> CommandBuffers;
            std::unique_ptr<anvSwapChain> AnvilSwapChain;
            //anvImLayer ImLayer{anvDevice, WindowManager.Window, AnvilSwapChain};
            std::unique_ptr<anvModel> model;

            

            AnvilEngineApplication()
            {
                ENGINE_INFO("Starting Engine");
                ENGINE_INFO(glfwGetVersionString());
                LoadModels();
                CreatePipelineLayout();
                RecreateSwapChain();
                CreateCommandBuffers();
            }


            anvSwapChain EngineGetSwapChain()
            {
                //return AnvilSwapChain;
            }


            void RecreateSwapChain()
            {
                auto Extent = WindowManager.GetExtent();

                while (Extent.width == 0 || Extent.height == 0)
                {
                    Extent = WindowManager.GetExtent();
                    glfwWaitEvents();
                }

                vkDeviceWaitIdle(anvDevice.m_device);

                if (AnvilSwapChain == nullptr){
                    AnvilSwapChain = std::make_unique<anvSwapChain>(anvDevice, Extent);
                } else {
                    AnvilSwapChain = std::make_unique<anvSwapChain>(anvDevice, Extent, std::move(AnvilSwapChain));
                    if (AnvilSwapChain->imageCount() != CommandBuffers.size())
                    {
                        FreeCommandBuffers();
                        CreateCommandBuffers();
                    }
                }
                CreatePipeline();
            }


            void RecordCommandBuffer(int ImageIndex)
            {
                static int frame = 0;
                frame = (frame + 1) % 1000;

                VkCommandBufferBeginInfo beginInfo{};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                if (vkBeginCommandBuffer(CommandBuffers[ImageIndex], &beginInfo) != VK_SUCCESS)
                {
                    ENGINE_ERROR("Failed to begin recording command buffer");
                }

                VkRenderPassBeginInfo renderPassInfo{};
                renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
                renderPassInfo.renderPass = AnvilSwapChain->getRenderPass();
                renderPassInfo.framebuffer = AnvilSwapChain->getFrameBuffer(ImageIndex);

                renderPassInfo.renderArea.offset = {0, 0};
                renderPassInfo.renderArea.extent = AnvilSwapChain->getSwapChainExtent();

                std::array<VkClearValue, 2> clearValues{};
                clearValues[0].color = {0.01f, 0.01f, 0.01f, 1.0f};
                clearValues[1].depthStencil = {1.0f, 0};
                renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
                renderPassInfo.pClearValues = clearValues.data();

                vkCmdBeginRenderPass(CommandBuffers[ImageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

                VkViewport viewport{};
                viewport.x = 0.0f;
                viewport.y = 0.0f;
                viewport.width = static_cast<uint32_t>(AnvilSwapChain->getSwapChainExtent().width);
                viewport.height = static_cast<uint32_t>(AnvilSwapChain->getSwapChainExtent().height);
                viewport.minDepth = 0.0f;
                viewport.maxDepth = 1.0f;
                VkRect2D scissor{{0, 0}, AnvilSwapChain->getSwapChainExtent()};
                vkCmdSetViewport(CommandBuffers[ImageIndex], 0, 1, &viewport);
                vkCmdSetScissor(CommandBuffers[ImageIndex], 0, 1, &scissor);

                AnvilPipeline->Bind(CommandBuffers[ImageIndex]);
                model->Bind(CommandBuffers[ImageIndex]);

                for (int j = 0; j < 4; j++)
                {
                    PushConstantData push{};
                    push.offset = {-0.5f + frame * 0.002f, -0.4f + j * 0.25f};
                    push.color = {0.0f, 0.0f, 0.2f + 0.2f * j};

                    vkCmdPushConstants(
                        CommandBuffers[ImageIndex], 
                        pipelineLayout, 
                        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 
                        0, 
                        sizeof(PushConstantData), &push);
                    model->Draw(CommandBuffers[ImageIndex]);
                }

                vkCmdEndRenderPass(CommandBuffers[ImageIndex]);
                if (vkEndCommandBuffer(CommandBuffers[ImageIndex]) != VK_SUCCESS)
                {
                    ENGINE_ERROR("Failed to record command buffer");
                }
            }


            void CreatePipelineLayout()
            {
                VkPushConstantRange pushConstantRange{};
                pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
                pushConstantRange.offset = 0;
                pushConstantRange.size = sizeof(PushConstantData);

                VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
                pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                pipelineLayoutInfo.setLayoutCount = 0;
                pipelineLayoutInfo.pSetLayouts = nullptr;
                pipelineLayoutInfo.pushConstantRangeCount = 1;
                pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
                if (vkCreatePipelineLayout(anvDevice.m_device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS){
                    ENGINE_ERROR("Failed to create pipeline layout");
                }
            }



            void CreatePipeline()
            {

                PipelineCfgInfo pipelineInfo{};
                auto pipelineConfig = anvPipeline::DefaultPipelinecfgInfo(pipelineInfo);
                pipelineConfig.renderPass = AnvilSwapChain->getRenderPass();
                pipelineConfig.pipelineLayout = pipelineLayout;
                AnvilPipeline = std::make_unique<anvPipeline>(
                    anvDevice, 
                    "shaders/vshader.spv", 
                    "shaders/fshader.spv", 
                    pipelineConfig);
            }



            void CreateCommandBuffers()
            {
                CommandBuffers.resize(AnvilSwapChain->imageCount());

                VkCommandBufferAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocInfo.commandPool = anvDevice.commandPool;
                allocInfo.commandBufferCount = static_cast<uint32_t>(CommandBuffers.size());

                if (vkAllocateCommandBuffers(anvDevice.m_device, &allocInfo, CommandBuffers.data()) != VK_SUCCESS)
                {
                    ENGINE_ERROR("Failed to allocate command buffers");
                }
            }



            void FreeCommandBuffers()
            {
                vkFreeCommandBuffers(anvDevice.m_device, anvDevice.commandPool, static_cast<float>(CommandBuffers.size()), CommandBuffers.data());
                CommandBuffers.clear();
            }


            void DrawFrame()
            {
                uint32_t imgIndex;
                auto result = AnvilSwapChain->acquireNextImage(&imgIndex);

                if (result == VK_ERROR_OUT_OF_DATE_KHR)
                {
                    RecreateSwapChain();
                }

                if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
                {
                    ENGINE_ERROR("Failed to aquire swap chain image");
                }
                
                //ImLayer.ImDraw(CommandBuffers[imgIndex]);
                RecordCommandBuffer(imgIndex);
                result = AnvilSwapChain->submitCommandBuffers(&CommandBuffers[imgIndex], &imgIndex);

                if (result == VK_ERROR_OUT_OF_DATE_KHR || VK_SUBOPTIMAL_KHR || WindowManager.WasWindowResized())
                {
                    WindowManager.ResetWindowResizedFlag();
                    RecreateSwapChain();
                    return;
                }
                if (result != VK_SUCCESS)
                {
                    ENGINE_ERROR("Failed to present swap chain image");
                }
            }


            void Run(){
                ENGINE_INFO("Running. . .");
                while (!glfwWindowShouldClose(WindowManager.Window)){

                    //ImGui::Begin("Hello World!");
            

                    glfwPollEvents();
                    DrawFrame();
                }
            }

            


            void LoadModels()
            {
                std::vector<anvModel::Vertex> vertices{
                    /*{{position}, {color}}*/

                    /*TRIANGLE 1*/
                    {{0.0f, -0.5f},{1.0f, 0.0f, 0.0f}},
                    {{0.5f, 0.5f},{0.0f, 1.0f, 0.0f}},
                    {{-0.5f, 0.5f},{0.0f, 0.0f, 1.0f}}
                    
                };

                model = std::make_unique<anvModel>(anvDevice, vertices);
            }

    };

}
