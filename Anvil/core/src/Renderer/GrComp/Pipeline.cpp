#include "Pipeline.h"
#include "Renderer/Devices.h"
#include "Renderer/Renderer.h"
#include "Scene/Components.h"
#include "Util/anvLog.hpp"
#include "Renderer/UBO.h"
#include <vulkan/vulkan.h>


namespace Anvil
{

	Ref<Pipeline> Pipeline::Create(std::vector<Ref<Shader>> _shaders, const PipelineInfo& _pi)
	{
		return CreateRef<Pipeline>(_shaders, _pi);
	}

    Pipeline::Pipeline(std::vector<Ref<Shader>> _shaders, const PipelineInfo& _pi)
    {
        m_ShaderStages.clear();
        process_shaders(_shaders);
        create_vk_pipeline(_pi);
    }
    
    Pipeline::~Pipeline()
    {

    }

    void Pipeline::Bind(CommandBuffer* cmdBuffer)
    {
        vkCmdBindPipeline(cmdBuffer->Get(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline);
    }

    VkDescriptorSetLayout& Pipeline::GetDescriptorLayout()
    {
        return m_DescriptorSetLayout;
    }

    VkPipelineLayout& Pipeline::GetPipelineLayout()
    {
        return m_Layout;
    }

    // Creates a shader stage for the pipeline
	void Pipeline::process_shaders(std::vector<Ref<Shader>> _shaders)
	{
        for (auto& shader : _shaders)
        {
            VkPipelineShaderStageCreateInfo info{};
            info.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            info.stage  = shader->GetStage();
            info.module = shader->GetModule();
            info.pName  = "main";

            m_ShaderStages.push_back(info);
        }
	}

	void Pipeline::create_vk_pipeline(const PipelineInfo& _pi)
	{
        bool HasDstSet = false;
        // If we have descriptor sets, we need to create a set layout
        if (!_pi.DstSetLayoutBindings.empty())
        {
            HasDstSet = true;

            VkDescriptorSetLayoutCreateInfo layoutInfo{};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = _pi.DstSetLayoutBindings.size();
            layoutInfo.pBindings = _pi.DstSetLayoutBindings.data();

            if (vkCreateDescriptorSetLayout(Devices::GetInstance()->Device(), &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
                ENGINE_WARN("Failed to create descriptor set layout!");
            }
        }
        
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = (HasDstSet) ? 1 : 0 ;
        pipelineLayoutInfo.pSetLayouts    = (HasDstSet) ? &m_DescriptorSetLayout : 0;

        if (!_pi.PushConstantRanges.empty())
        {
            pipelineLayoutInfo.pushConstantRangeCount = _pi.PushConstantRanges.size();
            pipelineLayoutInfo.pPushConstantRanges = _pi.PushConstantRanges.data();
        }

        if (vkCreatePipelineLayout(Devices::GetInstance()->Device(), &pipelineLayoutInfo, nullptr, &m_Layout) != VK_SUCCESS) {
            ENGINE_WARN("Failed to create pipeline layout");
        }

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = m_ShaderStages.size();
        pipelineInfo.pStages = m_ShaderStages.data();
        pipelineInfo.pVertexInputState = &_pi.vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &_pi.asmInputInfo;
        pipelineInfo.pDepthStencilState = &_pi.depthInfo;
        pipelineInfo.pViewportState = &_pi.viewportInfo;
        pipelineInfo.pRasterizationState = &_pi.rasterizerInfo;
        pipelineInfo.pMultisampleState = &_pi.multisampleInfo;
        pipelineInfo.pColorBlendState = &_pi.colorBlendInfo;
        pipelineInfo.pDynamicState = &_pi.dynamicInfo;
        pipelineInfo.layout = m_Layout;
        // Might want to leave render pass up to systems
        pipelineInfo.renderPass = Renderer::GetRenderPass()->Get();
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(Devices::GetInstance()->Device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_Pipeline) != VK_SUCCESS) {
            ENGINE_ERROR("Failed to create pipeline");
        }

        ENGINE_INFO("Created Pipeline");
	}

}