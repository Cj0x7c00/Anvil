#include "Renderer.h"
#include "Devices.h"
#include "SwapChain.h"


#include "Util/Time/Time.h"
#include "GrComp/Shader.h"

#include <vulkan/vulkan.h>

Anvil::Ref<Anvil::Devices>   Anvil::Renderer::m_Devices	     = nullptr;
Anvil::Ref<Anvil::SwapChain> Anvil::Renderer::m_SwapChain    = nullptr;
Anvil::Ref<Anvil::Window>    Anvil::Renderer::m_Window       = nullptr;

Anvil::Ref<Anvil::RenderSystem>    Anvil::Renderer::m_RenderSystem = nullptr;

VkRenderPass   Anvil::Renderer::m_RenderPass = VK_NULL_HANDLE;


namespace Anvil
{
	void Renderer::Init(Ref<Window> window)
	{
		Time::Profile("Renderer::Init");

		ENGINE_DEBUG("Renderer initializing");

		// initialize Vulkan specific stuff
		m_Devices   = Devices::Init(window);
		m_SwapChain = SwapChain::Create();

        create_render_pass();

        UseDefaultConfiguration();
	}

    void Renderer::UseSystem(Ref<RenderSystem> _system)
    {
        m_RenderSystem = _system;
    }

    void Renderer::UseDefaultConfiguration()
    {
        ENGINE_INFO("Using default render system");
        m_RenderSystem = RenderSystem::Default();
        m_RenderSystem->Init();
    }

	void Renderer::create_render_pass()
	{
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = m_SwapChain->GetFormat();
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        if (vkCreateRenderPass(m_Devices->Device(), &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS) {
            ENGINE_WARN("Failed to create render pass");
        }
	}

}

