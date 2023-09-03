#include "anvApplication.hpp"

#include "./Vulkan/simpleRenderSystem.hpp"

namespace Anvil{



        AnvilApplication::AnvilApplication()
        {
            //LoadGameObjecs();
            vkDeviceWaitIdle(anvDevice.m_device);
        }

        void AnvilApplication::PushLayer(AnvilLayer* layer)
        {
            ENGINE_ASSERT((layer != nullptr) && "No Layer to push onto layer stack");
            ENGINE_DEBUG("Pushing Layer: " + layer->GetName(), "`PushLayer()`");
            LayerStack.PushLayer(layer);
            layer->Attach();
        }

        void AnvilApplication::Run(){

            SimpleRenderSystem sRenderSystem{anvDevice, AnvRenderer.getSwapChainRenderPass()};

            for (AnvilLayer* layer : LayerStack.Layers)
            {
                auto name = layer->GetName();
                ENGINE_INFO("Loaded Layer: " + name, "`Run()`");
            }

            while (!glfwWindowShouldClose(WindowManager.windows[0])){

                glfwPollEvents();

                if (auto commandBuffer = AnvRenderer.BeginFrame())
                {
                    // update systems
                    float time = (float)glfwGetTime();
                    Timestep timestep = time - LastFrame;
                    LastFrame = time;

                    AnvRenderer.BeginSwapChainRenderPass(commandBuffer);
                    sRenderSystem.RenderGameObjects(commandBuffer, GameObjects, timestep);
                    AnvRenderer.EndSwapChainRenderPass(commandBuffer);
                    AnvRenderer.EndFrame();

                    for (AnvilLayer* layer : LayerStack.Layers)
                    {
                        layer->Update(timestep);
                    }
                }
                
            }

            vkDeviceWaitIdle(anvDevice.m_device);
        }

}



