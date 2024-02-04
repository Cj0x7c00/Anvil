#pragma once
#include "../../Base/Pointer.hpp"
#include "../../Base/macros.hpp"
#include "../CommandBuffer.h"
#include "Shader.h"
#include <vector>
#include <vulkan/vulkan.h>

namespace Anvil
{
    class ANV_API Pipeline
    {
    public:
        static Ref<Pipeline> Create(std::vector<Ref<Shader>> _shaders);

        Pipeline(std::vector<Ref<Shader>> _shaders);

        ~Pipeline();

        void Bind(CommandBuffer* cmdBuffer);
        VkDescriptorSetLayout& GetDescriptorLayout();
        VkPipelineLayout& GetPipelineLayout();

    private:
        void process_shaders(std::vector<Ref<Shader>> _shaders);
        void create_descriptor_layout();
        void create_pipeline_layout();

    private:
        VkPipeline       m_Pipeline;
        VkPipelineLayout m_Layout;

        VkDescriptorSetLayout m_DescriptorSetLayout;

        std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages;
    };
}

