#include "Renderer.h"
#include "Devices.h"
#include "SwapChain.h"


#include "Util/Time/Time.h"
#include "GrComp/Shader.h"

#include <vulkan/vulkan.h>

Anvil::Ref<Anvil::Devices>      Anvil::Renderer::m_Devices	    = nullptr;
Anvil::Ref<Anvil::SwapChain>    Anvil::Renderer::m_SwapChain    = nullptr;
Anvil::Ref<Anvil::Window>       Anvil::Renderer::m_Window       = nullptr;
Anvil::Ref<Anvil::RenderSystem> Anvil::Renderer::m_RenderSystem = nullptr;
Anvil::Ref<Anvil::RenderPass>   Anvil::Renderer::m_RenderPass   = nullptr;

VkCommandBuffer   Anvil::Renderer::m_CommandBuffer = VK_NULL_HANDLE;

VkSemaphore Anvil::Renderer::m_ImageAvailableSemaphore = VK_NULL_HANDLE;
VkSemaphore Anvil::Renderer::m_RenderFinishedSemaphore = VK_NULL_HANDLE;
VkFence     Anvil::Renderer::m_InFlightFence           = VK_NULL_HANDLE;



namespace Anvil
{
	void Renderer::Init(Ref<Window> window)
	{
		auto t = Time::Profile("Renderer::Init");

		ENGINE_DEBUG("Renderer initializing");

		// initialize Vulkan specific stuff
		m_Devices   = Devices::Init(window);

		m_SwapChain = SwapChain::Create();
        create_render_pass();
        m_SwapChain->CreateFrameBuffers(m_RenderPass->Get());

        UseDefaultConfiguration();

        sync();
	}

    void Renderer::UseSystem(Ref<RenderSystem> _system)
    {
        m_RenderSystem = _system;
    }

    void Renderer::UseDefaultConfiguration()
    {
        ENGINE_INFO("Using default render system");
        m_RenderSystem = RenderSystem::Default(m_SwapChain);
        m_RenderSystem->Init();
    }

    void Renderer::NewFrame()
    {
        auto time = Time::Profile("Renderer::NewFrame");
        vkWaitForFences(m_Devices->Device(), 1, &m_InFlightFence, VK_TRUE, UINT64_MAX);

        uint32_t ImageIndex;
        vkAcquireNextImageKHR(m_Devices->Device(), m_SwapChain->GetSwapChain(), UINT64_MAX, 
            m_ImageAvailableSemaphore, VK_NULL_HANDLE, &ImageIndex);

        m_RenderSystem->NewFrame(m_RenderPass, ImageIndex);
        vkResetFences(m_Devices->Device(), 1, &m_InFlightFence);

        submit();
        present(ImageIndex);

        //m_RenderSystem->Flush();
    }

    void Renderer::WaitIdle()
    {
        vkDeviceWaitIdle(m_Devices->Device());
    }

    void Renderer::create_render_pass()
	{
        m_RenderPass = RenderPass::Create(m_SwapChain);
	}

    void Renderer::sync()
    {
        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        if (vkCreateSemaphore(m_Devices->Device(), &semaphoreInfo, nullptr, &m_ImageAvailableSemaphore) != VK_SUCCESS ||
            vkCreateSemaphore(m_Devices->Device(), &semaphoreInfo, nullptr, &m_RenderFinishedSemaphore) != VK_SUCCESS ||
            vkCreateFence(m_Devices->Device(), &fenceInfo, nullptr, &m_InFlightFence) != VK_SUCCESS) {
            throw std::runtime_error("failed to create semaphores!");
        }
    }

    void Renderer::submit()
    {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphore };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &m_RenderSystem->GetCommandBuffer()->Get();

        VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphore };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(m_Devices->GraphicsQueue(), 1, &submitInfo, m_InFlightFence) != VK_SUCCESS) {
            ENGINE_WARN("Failed to submit command buffer");
        }

    }

    void Renderer::present(uint32_t imgIndex)
    {
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = {&m_RenderFinishedSemaphore};
        VkSwapchainKHR swapChains[] = { m_SwapChain->GetSwapChain()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imgIndex;
        presentInfo.pResults = nullptr; // Optional

        vkQueuePresentKHR(m_Devices->PresentQueue(), &presentInfo);
        m_RenderSystem->Flush();

    }

}

