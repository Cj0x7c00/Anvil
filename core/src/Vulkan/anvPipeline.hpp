#pragma once
#include "../Util/anvLog.hpp"
#include "../anvpch.hpp"
#include "anvDevice.hpp"

namespace Anvil
{
    struct PipelineCfgInfo{
        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicStateinfo; 
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };
    
    class anvPipeline
    {

    public:
        anvPipeline(
            AnvDevice& anv_device, 
            const std::string& vertFilepath, 
            const std::string& fragFilepath,
            const PipelineCfgInfo& cfginfo);

        ~anvPipeline();

        anvPipeline(const anvPipeline&) = delete;
        anvPipeline &operator=(const anvPipeline&) = delete;

        void Bind(VkCommandBuffer commandBuffer);
 
        static PipelineCfgInfo DefaultPipelinecfgInfo(PipelineCfgInfo& configInfo);

        static std::vector<char> ReadFile(const std::string& filepath);

        void CreateGraphicsPipeline(
            const std::string& vertFilepath, 
            const std::string& fragFilepath,  
            const PipelineCfgInfo& cfginfo);

        void CreateShaderModule(const std::vector<char> code, VkShaderModule* shader_mod);

    private:
        AnvDevice& device;
        VkPipeline graphicsPipeline;
        VkShaderModule vert_mod;
        VkShaderModule frag_mod;

        bool pipelineCeated = false;

    };
    
} // namespace Anvil
