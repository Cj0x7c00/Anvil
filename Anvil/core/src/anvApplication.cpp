#include "anvApplication.hpp"
#include "./Vulkan/simpleRenderSystem.hpp"

namespace Anvil{



        AnvilApplication::AnvilApplication()
        {
            WindowProps p;
            m_Window = Window::Create(p);

            AnvDevice::DeviceInit(m_Window->Get());
            anvDevice = AnvDevice::GetInstance();

            AnvRenderer = new anvRenderer{ m_Window, anvDevice };

            LoadGameObjects();

            vkDeviceWaitIdle(anvDevice->m_device);
        }

        void AnvilApplication::PushLayer(AnvilLayer* layer)
        {
            ENGINE_ASSERT((layer != nullptr) && "No Layer to push onto layer stack");
            ENGINE_DEBUG("Pushing Layer: " + layer->GetName());
            LayerStack.PushLayer(layer);
            layer->Attach();
        }

        void AnvilApplication::Run(){

            SimpleRenderSystem sRenderSystem{anvDevice, AnvRenderer->getSwapChainRenderPass()};

            for (AnvilLayer* layer : LayerStack.Layers)
            {
                auto name = layer->GetName();
                ENGINE_INFO("Loaded Layer: " + name);
            }

            while (!m_Window->ShouldClose()){

                glfwPollEvents();

                if (auto commandBuffer = AnvRenderer->BeginFrame())
                {
                    // update systems
                    float time = (float)glfwGetTime();
                    Timestep timestep = time - LastFrame;
                    LastFrame = time;

                    AnvRenderer->BeginSwapChainRenderPass(commandBuffer);
                    sRenderSystem.RenderGameObjects(commandBuffer, GameObjects, timestep);
                    AnvRenderer->EndSwapChainRenderPass(commandBuffer);
                    AnvRenderer->EndFrame();

                    for (AnvilLayer* layer : LayerStack.Layers)
                    {
                        layer->Update(timestep);
                    }
                }
                
            }

            vkDeviceWaitIdle(anvDevice->m_device);
        }

        std::unique_ptr<anvModel> createCubeModel(Ref<AnvDevice> device, glm::vec3 offset) {
            std::vector<anvModel::Vertex> vertices{
            
                // left face (white)
                {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
                {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
                {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
                {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
                {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},
                {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
            
                // right face (yellow)
                {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
                {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
                {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
                {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
                {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},
                {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
            
                // top face (orange, remember y axis points down)
                {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
                {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
                {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
                {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
                {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
                {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            
                // bottom face (red)
                {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
                {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
                {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
                {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
                {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},
                {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
            
                // nose face (blue)
                {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
                {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
                {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
                {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
                {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
                {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            
                // tail face (green)
                {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
                {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
                {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            
            };
            for (auto& v : vertices) {
                v.position += offset;
            }
            return std::make_unique<anvModel>(device, vertices);
            }

        void AnvilApplication::LoadGameObjects()
        {
            std::shared_ptr<anvModel> model1 = createCubeModel(anvDevice, {.0f, .0f, .0f});
            auto cube = anvGameObject::CreateGameObject();
            cube.model = model1;
            cube.transform.translation = {.0f, .0f, .5f};
            cube.transform.scale = {.5f, .5f, .5f};
            GameObjects.push_back(std::move(cube));
        }

}



