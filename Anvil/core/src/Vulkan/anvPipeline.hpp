#pragma once
#include "../Util/anvLog.hpp"
#include "../anvpch.hpp"
#include "VkShader.h"
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
            Ref<AnvDevice> anv_device, 
            const std::string& vertFilepath, 
            const std::string& fragFilepath,
            const PipelineCfgInfo& cfginfo);

        ~anvPipeline();

        anvPipeline(const anvPipeline&) = delete;
        anvPipeline &operator=(const anvPipeline&) = delete;

        void Bind(VkCommandBuffer commandBuffer);
 
        static PipelineCfgInfo DefaultPipelinecfgInfo(PipelineCfgInfo& configInfo);

        void CreateGraphicsPipeline(
            const std::string& vertFilepath, 
            const std::string& fragFilepath,  
            const PipelineCfgInfo& cfginfo);

    private:
        Ref<AnvDevice>  device;
        VkPipeline      graphicsPipeline;
        Ref<VkShader>  vert_mod;
        Ref<VkShader>  frag_mod;

        bool pipelineCeated = false;

    };
    
} // namespace Anvil
