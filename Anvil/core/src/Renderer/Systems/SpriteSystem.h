#pragma once
#include "Base/Pointer.hpp"
#include "Scene/Components.h"
#include "../UBO.h"
#include "../RenderSystem.h"
#include "../Renderer.h"
#include "../GrComp/GraphicsFactory.h"

#include <vector>
#include <Util/anvLog.hpp>

namespace Anvil
{
    struct PushConstantData
    {
        glm::mat4 model;
        glm::vec3 color;
    };

    struct UniformBufferObject {
        glm::mat4 view;
        glm::mat4 proj;
    };

    class SpriteSystem :
        public RenderSystem
    {
    public:

        SpriteSystem(Ref<SwapChain> _sc) : RenderSystem(_sc)
        {
            ENGINE_INFO("Creating Sprite System");
        }
        
        ~SpriteSystem();

        void Init() override;
        
        void OnCallOnce(CommandBuffer cmdBuffer) override;
        
        void Update(NewFrameInfo& frameInfo) override;
        
        void NewFrame(NewFrameInfo& frameInfo) override;
        
        void create_ubo();
        
        void update_ubos(NewFrameInfo& frameInfo, TransformComponent& trans);
        
        void create_descriptor_pool();
        
        void create_descriptor_sets();

    private:
        void load_shaders();
        void create_pipeline();

    private:

        std::vector<VkBuffer>       m_UniformBuffers;
        std::vector<void*>          m_UniformBuffersMapped;
        std::vector<VkDeviceMemory> m_UniformBuffersMemory;

        VkDescriptorPool m_DescriptorPool;
        std::vector<VkDescriptorSet> m_DescriptorSets;

        Ref<Pipeline>            m_Pipeline;
        std::vector<Ref<Shader>> m_Shaders;
    };
}

