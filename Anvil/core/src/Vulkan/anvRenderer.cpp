#include "anvRenderer.hpp"

namespace Anvil{

    anvRenderer::anvRenderer(WindowManager &Window, AnvDevice& device) : Window{Window}, anvDevice{device}
    {
        ENGINE_INFO("Initializing Renderer", "`anvRenderer()`");
        RecreateSwapChain();
        CreateCommandBuffers();
    }


    anvRenderer::~anvRenderer(){ FreeCommandBuffers(); vkDeviceWaitIdle(anvDevice.m_device); }

    void anvRenderer::RecreateSwapChain()
    {
        auto Extent = Window.GetExtent();

        while (Extent.width == 0 || Extent.height == 0)
        {
            Extent = Window.GetExtent();
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(anvDevice.m_device); //

        if (AnvilSwapChain == nullptr){
            AnvilSwapChain = std::make_unique<anvSwapChain>(anvDevice, Extent);
        } else {
            std::shared_ptr<anvSwapChain> oldSwpChn = std::move(AnvilSwapChain);
            AnvilSwapChain = std::make_unique<anvSwapChain>(anvDevice, Extent, oldSwpChn);

            if (!oldSwpChn->CompareSwapFormats(*AnvilSwapChain.get()))
            {
              ENGINE_WARN("Swapchain image(or depth formats) have changed", "`RecreateSwapChain()`");
            }

        }
    }

    void anvRenderer::CreateCommandBuffers()
    {
        CommandBuffers.resize(AnvilSwapChain->MAX_FRAMES_IN_FLIGHT);

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = anvDevice.commandPool;
        allocInfo.commandBufferCount = static_cast<uint32_t>(CommandBuffers.size());

        if (vkAllocateCommandBuffers(anvDevice.m_device, &allocInfo, CommandBuffers.data()) != VK_SUCCESS)
        {
            ENGINE_ERROR("Failed to allocate command buffers", "`CreateCommandBuffers()`");
        }
    }



    void anvRenderer::FreeCommandBuffers()
    {
        vkFreeCommandBuffers(anvDevice.m_device, anvDevice.commandPool, static_cast<float>(CommandBuffers.size()), CommandBuffers.data());
        CommandBuffers.clear();
    }

VkCommandBuffer anvRenderer::BeginFrame() {
  assert(!isFrameStarted && "Can't call beginFrame while already in progress");

  auto result = AnvilSwapChain->acquireNextImage(&currentImageIndex);
  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    RecreateSwapChain();
    return nullptr;
  }

  if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error("failed to acquire swap chain image!");
  }

  isFrameStarted = true;

  auto commandBuffer = getCurrentCommandBuffer();
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

  vkDeviceWaitIdle(anvDevice.m_device);

  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    ENGINE_ERROR("failed to begin recording command buffer!", "`BeginFrame()`");
  }
  return commandBuffer;
}

void anvRenderer::EndFrame() {
  assert(isFrameStarted && "Can't call endFrame while frame is not in progress");
  auto commandBuffer = getCurrentCommandBuffer();
  if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to record command buffer!");
  }

  auto result = AnvilSwapChain->submitCommandBuffers(&commandBuffer, &currentImageIndex);
  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
      Window.WasWindowResized()) {
    Window.ResetWindowResizedFlag();
    RecreateSwapChain();
  } else if (result != VK_SUCCESS) {
    throw std::runtime_error("failed to present swap chain image!");
  }

  isFrameStarted = false;
  currentFrameIndex = (currentImageIndex + 1) % AnvilSwapChain->MAX_FRAMES_IN_FLIGHT;
}

void anvRenderer::BeginSwapChainRenderPass(VkCommandBuffer commandBuffer) {
  assert(isFrameStarted && "Can't call beginSwapChainRenderPass if frame is not in progress");
  assert(
      commandBuffer == getCurrentCommandBuffer() &&
      "Can't begin render pass on command buffer from a different frame");

  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = AnvilSwapChain->getRenderPass();
  renderPassInfo.framebuffer = AnvilSwapChain->getFrameBuffer(currentImageIndex);

  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = AnvilSwapChain->getSwapChainExtent();

  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {0.01f, 0.01f, 0.01f, 1.0f};
  clearValues[1].depthStencil = {1.0f, 0};
  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = static_cast<float>(AnvilSwapChain->getSwapChainExtent().width);
  viewport.height = static_cast<float>(AnvilSwapChain->getSwapChainExtent().height);
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  VkRect2D scissor{{0, 0}, AnvilSwapChain->getSwapChainExtent()};
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void anvRenderer::EndSwapChainRenderPass(VkCommandBuffer commandBuffer) {
  assert(isFrameStarted && "Can't call endSwapChainRenderPass if frame is not in progress");
  assert(
      commandBuffer == getCurrentCommandBuffer() &&
      "Can't end render pass on command buffer from a different frame");
  vkCmdEndRenderPass(commandBuffer);
}

}  // namespace lve