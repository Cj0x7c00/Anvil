#include "Renderer.h"
#include "Devices.h"
#include "SwapChain.h"
#include "CommandBuffer.h"
#include "RenderSystem.h"
#include "Util/Time/Time.h"
#include "GrComp/Shader.h"

#include <vulkan/vulkan.h>

Anvil::Ref<Anvil::Devices>      Anvil::Renderer::m_Devices	    = nullptr;
Anvil::Ref<Anvil::SwapChain>    Anvil::Renderer::m_SwapChain    = nullptr;
Anvil::Ref<Anvil::Window>       Anvil::Renderer::m_Window       = nullptr;
Anvil::SceneManager*            Anvil::Renderer::m_SceneManager = nullptr;

Anvil::NewFrameInfo                           Anvil::Renderer::m_FrameInfo      = {};
std::vector<Anvil::Ref<Anvil::RenderSystem>>  Anvil::Renderer::m_RenderSystems  = {};
std::vector<Anvil::Ref<Anvil::CommandBuffer>> Anvil::Renderer::m_CommandBuffers = {};

std::vector<VkFence>     Anvil::Renderer::m_InFlightFences           = { VK_NULL_HANDLE };
std::vector<VkSemaphore> Anvil::Renderer::m_ImageAvailableSemaphores = { VK_NULL_HANDLE };
std::vector<VkSemaphore> Anvil::Renderer::m_RenderFinishedSemaphores = { VK_NULL_HANDLE };


namespace Anvil
{
	void Renderer::Init(Ref<Window> window, SceneManager* _scene_manager)
	{
		ENGINE_DEBUG("Renderer initializing");
		auto t = Time::Profile("Renderer::Init");
        m_Window = window;

		// initialize Vulkan specific stuff
		m_Devices   = Devices::Init(m_Window);

		m_SwapChain = SwapChain::Create();
        create_render_pass();
        m_SwapChain->CreateFrameBuffers(m_FrameInfo.RenderPass->Get());

        m_SceneManager = _scene_manager;

        // Create command buffers
        for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
            m_CommandBuffers.push_back(CommandBuffer::Create());
        }


        InitCoreSystems();

        sync();
	}

    void Renderer::UseSystem(Ref<RenderSystem> _system)
    {
        m_RenderSystems.push_back(_system);
    }

    void Renderer::InitCoreSystems()
    {
        ENGINE_INFO("Using default render system");
        m_RenderSystems = RenderSystem::Default(m_SwapChain);
        for (auto& system : m_RenderSystems)
        {
            system->Init();
        }
    }

    void Renderer::BeginOneTimeOps()
    {
        CommandBuffer singleCmds;
        singleCmds.BeginRecording();


        for (auto& system : m_RenderSystems)
        {
            system->OnCallOnce(singleCmds);
        }

        singleCmds.EndRecording();
        SubmitOneTimeCommands(singleCmds);
    }

    void Renderer::OnSingleTimeCommand(std::function<void(CommandBuffer cmdBuffer)> _Fn)
    {
        CommandBuffer singleCmds;
        singleCmds.BeginRecording();

        _Fn(singleCmds);

        singleCmds.EndRecording();
        SubmitOneTimeCommands(singleCmds);
    }

    void Renderer::NewFrame()
    {
        for (auto& system : m_RenderSystems)
        {
            m_FrameInfo.Scene = m_SceneManager->GetActiveScene();
            vkWaitForFences(m_Devices->Device(), 1, &m_InFlightFences[m_FrameInfo.ImageIndex], VK_TRUE, UINT64_MAX);

            auto result = vkAcquireNextImageKHR(m_Devices->Device(), m_SwapChain->GetSwapChain(), UINT64_MAX,
                m_ImageAvailableSemaphores[m_FrameInfo.FrameIndex], VK_NULL_HANDLE, &m_FrameInfo.ImageIndex);

            m_FrameInfo.CommandBuffer = m_CommandBuffers[m_FrameInfo.ImageIndex];

            check_swapchain_suitability(result);
            vkResetFences(m_Devices->Device(), 1, &m_InFlightFences[m_FrameInfo.ImageIndex]);

            m_FrameInfo.CommandBuffer->Reset();

            for (auto& sys : m_RenderSystems)
            {
                sys->NewFrame(m_FrameInfo);
            }

            m_FrameInfo.CommandBuffer->EndRecording(m_FrameInfo);

           Submit(m_FrameInfo);
        }

        m_FrameInfo.FrameIndex = (m_FrameInfo.FrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void Renderer::WaitIdle()
    {
        vkDeviceWaitIdle(m_Devices->Device());
    }

    void Renderer::SetViewport(ViewportInfo& info, CommandBuffer* cmdBuff)
    {

        VkViewport viewport{};
        viewport.x = info.x;
        viewport.y = info.y;
        viewport.width = info.width;
        viewport.height = info.height;
        viewport.minDepth = info.minDepth;
        viewport.maxDepth = info.maxDepth;
        vkCmdSetViewport(cmdBuff->Get(), 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent.width = info.scissorExtent.width;
        scissor.extent.height = info.scissorExtent.height;

        vkCmdSetScissor(cmdBuff->Get(), 0, 1, &scissor);

    }

    void Renderer::CreateNewSwapChain()
    {
        // Window minimization
        {
            int width = 0, height = 0;
            glfwGetFramebufferSize((GLFWwindow*)m_Window->Get(), &width, &height);
            while (width == 0 || height == 0) {
                glfwGetFramebufferSize((GLFWwindow*)m_Window->Get(), &width, &height);
                glfwWaitEvents();
            }
        }

        WaitIdle();

        for (size_t i = 0; i < m_SwapChain->GetFrameBuffers().size(); i++) {
            vkDestroyFramebuffer(m_Devices->Device(), m_SwapChain->GetFrameBuffers()[i], nullptr);
        }

        for (size_t i = 0; i < m_SwapChain->GetImageViews().size(); i++) {
            vkDestroyImageView(m_Devices->Device(), m_SwapChain->GetImageViews()[i], nullptr);
        }

        vkDestroySwapchainKHR(m_Devices->Device(), m_SwapChain->GetSwapChain(), nullptr);

        m_SwapChain = SwapChain::Create();
        m_SwapChain->CreateFrameBuffers(m_FrameInfo.RenderPass->Get());

    }

    void Renderer::WindowWasResized()
    {
        CreateNewSwapChain();
        create_render_pass();

        RenderSystem::WindowWasResized(m_SwapChain);
    }

    Ref<SwapChain> Renderer::GetSwapChain()
    {
        return m_SwapChain;
    }

    Ref<Window> Renderer::GetWindow()
    {
        return m_Window;
    }

    void Renderer::create_render_pass()
	{
        m_FrameInfo.RenderPass = RenderPass::Create(m_SwapChain);
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

    void Renderer::Submit(NewFrameInfo& _fi)
    {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphores[m_FrameInfo.FrameIndex] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &_fi.CommandBuffer->Get();

        VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphores[m_FrameInfo.ImageIndex]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(m_Devices->GraphicsQueue(), 1, &submitInfo, m_InFlightFences[m_FrameInfo.ImageIndex]) != VK_SUCCESS) {
            ENGINE_WARN("Failed to submit command buffer");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        VkSwapchainKHR swapChains[] = { m_SwapChain->GetSwapChain() };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &_fi.ImageIndex;
        presentInfo.pResults = nullptr; // Optional

        auto result = vkQueuePresentKHR(m_Devices->PresentQueue(), &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            CreateNewSwapChain();
        }
        else if (result != VK_SUCCESS) {
            ENGINE_WARN("Failed to present swap chain image!");
        }
    }

    void Renderer::SubmitOneTimeCommands(CommandBuffer cmdBuffer)
    {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &cmdBuffer.Get();

        vkQueueSubmit(m_Devices->GraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(m_Devices->GraphicsQueue());

        vkFreeCommandBuffers(m_Devices->Device(), m_Devices->CommandPool(), 1, &cmdBuffer.Get());
    }

    ViewportInfo ViewportInfo::Default()
    {
        ViewportInfo info;
        info.x = 0.0f;
        info.y = 0.0f;
        info.width = (float)Renderer::GetSwapChain()->GetExtent().width;
        info.height = (float)Renderer::GetSwapChain()->GetExtent().height;
        info.minDepth = 0.0f;
        info.maxDepth = 1.0f;
        info.scissorOffset[0] = 0;
        info.scissorOffset[1] = 0;
        info.scissorExtent.width = Renderer::GetSwapChain()->GetExtent().width;
        info.scissorExtent.height = Renderer::GetSwapChain()->GetExtent().height;
        return info;   
    }

}

