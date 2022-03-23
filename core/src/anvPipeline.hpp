#pragma once
#include "anvpch.hpp"
#include "vk_object.hpp"

namespace AnvilEngine
{
    struct PipelineCfgInfo{
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };
    
    class anvPipeline
    {

    public:
        anvPipeline(
            VK_OBJ& anv_device, 
            const std::string& vertFilepath, 
            const std::string& fragFilepath,
            const PipelineCfgInfo& cfginfo);

        ~anvPipeline();

        anvPipeline(const anvPipeline&) = delete;
        void operator=(const anvPipeline&) = delete;

        void Bind(VkCommandBuffer commandBuffer);
 
        static PipelineCfgInfo DefaultPipelinecfgInfo(uint32_t width, uint32_t height);

        static std::vector<char> ReadFile(const std::string& filepath);

        void CreateGraphicsPipeline(
            const std::string& vertFilepath, 
            const std::string& fragFilepath,  
            const PipelineCfgInfo& cfginfo);

        void CreateShaderModule(const std::vector<char> code, VkShaderModule* shader_mod);

    private:
        VkPipeline graphicsPipeline;
        VkShaderModule vert_mod;
        VkShaderModule frag_mod;
    };
    
} // namespace AnvilEngine
