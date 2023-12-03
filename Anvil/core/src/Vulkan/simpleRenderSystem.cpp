#include "simpleRenderSystem.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>



namespace Anvil{

    struct PushConstantData
    {
        glm::mat4 transform{1.f};
        alignas(16) glm::vec3 color;
    };

    SimpleRenderSystem::SimpleRenderSystem(AnvDevice& device, VkRenderPass renderPass) : anvDevice{device}
    {
        
        CreatePipelineLayout();
        CreatePipeline(renderPass);
        vkDeviceWaitIdle(anvDevice.m_device);
    }

    void SimpleRenderSystem::RenderGameObjects(VkCommandBuffer cmdbuffer, std::vector<anvGameObject> &GameObjects, Timestep ts)
    {
        AnvilPipeline->Bind(cmdbuffer);

        for (auto& obj: GameObjects){
            obj.transform.rotation.y = glm::mod(obj.transform.rotation.y + 1.0f * ts.GetSeconds(), glm::two_pi<float>()); // constant rotation
            obj.transform.rotation.x = glm::mod(obj.transform.rotation.x + 0.5f * ts.GetSeconds(), glm::two_pi<float>()); // constant rotation

            PushConstantData push{};
            push.color = obj.color;
            push.transform = obj.transform.mat4();

            vkCmdPushConstants(
                cmdbuffer, 
                pipelineLayout, 
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 
                0, 
                sizeof(PushConstantData), &push);

            obj.model->Bind(cmdbuffer);
            obj.model->Draw(cmdbuffer);
        }
    }


    void SimpleRenderSystem::CreatePipelineLayout()
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
            ENGINE_ERROR("Failed to create pipeline layout", "");
        }
    }

    void SimpleRenderSystem::CreatePipeline(VkRenderPass renderPass)
    {

        PipelineCfgInfo pipelineInfo{};
        auto pipelineConfig = anvPipeline::DefaultPipelinecfgInfo(pipelineInfo);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        AnvilPipeline = std::make_unique<anvPipeline>(
            anvDevice, 
            "C:/Dev/AnvEngine-org/Anvil-2D/Anvil/core/src/Vulkan/vert.glsl.spv",
            "C:/Dev/AnvEngine-org/Anvil-2D/Anvil/core/src/Vulkan/frag.glsl.spv",
            pipelineConfig);
    }
}



