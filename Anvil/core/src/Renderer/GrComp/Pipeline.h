#pragma once
#include "../../Base/Pointer.hpp"
#include "../../Base/macros.hpp"
#include "../CommandBuffer.h"
#include "Shader.h"
#include <vector>
#include <vulkan/vulkan.h>

namespace Anvil
{
    struct PipelineInfo
    {

        VkVertexInputBindingDescription    vertexBindingDesc;
        std::array<VkVertexInputAttributeDescription, 2> vertexAttrDesc;

        VkPipelineVertexInputStateCreateInfo    vertexInputInfo;
        VkPipelineInputAssemblyStateCreateInfo  asmInputInfo;
        VkPipelineViewportStateCreateInfo       viewportInfo;
        VkPipelineRasterizationStateCreateInfo  rasterizerInfo;
        VkPipelineMultisampleStateCreateInfo    multisampleInfo;
        VkPipelineColorBlendStateCreateInfo     colorBlendInfo;
        VkPipelineDynamicStateCreateInfo        dynamicInfo;

        std::vector<VkPushConstantRange> PushConstantRanges;
        std::vector<VkDescriptorSetLayoutBinding> DstSetLayoutBindings;

    };

    class ANV_API Pipeline
    {
    public:
        static Ref<Pipeline> Create(std::vector<Ref<Shader>> _shaders, const PipelineInfo& _pi);

        Pipeline(std::vector<Ref<Shader>> _shaders, const PipelineInfo& _pi);

        ~Pipeline();

        void Bind(CommandBuffer* cmdBuffer);
        VkDescriptorSetLayout& GetDescriptorLayout();
        VkPipelineLayout& GetPipelineLayout();

    private:
        void process_shaders(std::vector<Ref<Shader>> _shaders);
        //void create_descriptor_layout();
        void create_vk_pipeline(const PipelineInfo& _pi);

    private:
        VkPipeline       m_Pipeline;
        VkPipelineLayout m_Layout;

        VkDescriptorSetLayout m_DescriptorSetLayout;

        std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages;
    };
}

