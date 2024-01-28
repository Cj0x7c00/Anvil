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

std::vector<VkSemaphore> Anvil::Renderer::m_ImageAvailableSemaphores = { VK_NULL_HANDLE };
std::vector<VkSemaphore> Anvil::Renderer::m_RenderFinishedSemaphores = { VK_NULL_HANDLE };
std::vector<VkFence>     Anvil::Renderer::m_InFlightFences           = { VK_NULL_HANDLE };

uint32_t Anvil::Renderer::m_FrameIndex = 0;
uint32_t Anvil::Renderer::m_ImageIndex = 0;


namespace Anvil
{
	void Renderer::Init(Ref<Window> window)
	{
		auto t = Time::Profile("Renderer::Init");

		ENGINE_DEBUG("Renderer initializing");

        m_Window = window;

		// initialize Vulkan specific stuff
		m_Devices   = Devices::Init(m_Window);

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

        vkWaitForFences(m_Devices->Device(), 1, &m_InFlightFences[m_ImageIndex], VK_TRUE, UINT64_MAX);

        auto result = vkAcquireNextImageKHR(m_Devices->Device(), m_SwapChain->GetSwapChain(), UINT64_MAX,
            m_ImageAvailableSemaphores[m_FrameIndex], VK_NULL_HANDLE, &m_ImageIndex);
     
        check_swapchain_suitability(result);

        vkResetFences(m_Devices->Device(), 1, &m_InFlightFences[m_ImageIndex]);
        m_RenderSystem->Flush(m_ImageIndex);

        m_RenderSystem->NewFrame(m_RenderPass, m_ImageIndex);
        submit(m_ImageIndex);   

        m_FrameIndex = (m_FrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void Renderer::WaitIdle()
    {
        vkDeviceWaitIdle(m_Devices->Device());
    }

    void Renderer::CreateNewSwapChain()
    {

        WaitIdle();

        for (size_t i = 0; i < m_SwapChain->GetFrameBuffers().size(); i++) {
            vkDestroyFramebuffer(m_Devices->Device(), m_SwapChain->GetFrameBuffers()[i], nullptr);
        }

        for (size_t i = 0; i < m_SwapChain->GetImageViews().size(); i++) {
            vkDestroyImageView(m_Devices->Device(), m_SwapChain->GetImageViews()[i], nullptr);
        }

        vkDestroySwapchainKHR(m_Devices->Device(), m_SwapChain->GetSwapChain(), nullptr);

        m_SwapChain = SwapChain::Create();
        m_SwapChain->CreateFrameBuffers(m_RenderPass->Get());

    }

    void Renderer::WindowWasResized()
    {
        CreateNewSwapChain();
        create_render_pass();
        m_RenderSystem->WindowWasResized(m_SwapChain);
    }

    void Renderer::create_render_pass()
	{
        m_RenderPass = RenderPass::Create(m_SwapChain);
	}

    void Renderer::check_swapchain_suitability(VkResult res)
    {
        if (res == VK_ERROR_OUT_OF_DATE_KHR) {
            CreateNewSwapChain();
            return;
        }
        else if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
            ENGINE_WARN("failed to acquire swap chain image!");
        }

    }

    void Renderer::sync()
    {
        m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(m_Devices->Device(), &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(m_Devices->Device(), &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(m_Devices->Device(), &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS) {

                ENGINE_WARN("Failed to create sync objects");
            }
        }
    }

    void Renderer::submit(uint32_t imgIndex)
    {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphores[m_FrameIndex] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &m_RenderSystem->GetCommandBuffer(m_ImageIndex)->Get();

        VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphores[m_ImageIndex]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(m_Devices->GraphicsQueue(), 1, &submitInfo, m_InFlightFences[m_ImageIndex]) != VK_SUCCESS) {
            ENGINE_WARN("Failed to submit command buffer");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        VkSwapchainKHR swapChains[] = { m_SwapChain->GetSwapChain() };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imgIndex;
        presentInfo.pResults = nullptr; // Optional

        auto result = vkQueuePresentKHR(m_Devices->PresentQueue(), &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            CreateNewSwapChain();
        }
        else if (result != VK_SUCCESS) {
            ENGINE_WARN("Failed to present swap chain image!");
        }
    }

}

