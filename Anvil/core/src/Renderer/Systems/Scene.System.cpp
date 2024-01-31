#include "Scene.System.h"
#include "Util/Time/Time.h"
#include "../SwapChain.h"
#include "../GrComp/Pipeline.h"
#include <vulkan/vulkan.h>
#include <Util/anvLog.hpp>

namespace Anvil
{
	void SceneSys::Init()
	{
		load_shaders();
		create_pipeline();
	}

	void SceneSys::NewFrame(NewFrameInfo& frameInfo, Ref<Scene> scene)
	{
		m_CommandBuffers[frameInfo.ImageIndex]->BeginRecording();
		frameInfo.RenderPass->Begin(m_CommandBuffers[frameInfo.ImageIndex], frameInfo.ImageIndex);
		m_Pipeline->Bind(m_CommandBuffers[frameInfo.ImageIndex]);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(m_SwapChain->GetExtent().width);
		viewport.height = static_cast<float>(m_SwapChain->GetExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(m_CommandBuffers[frameInfo.ImageIndex]->Get(), 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = m_SwapChain->GetExtent();
		vkCmdSetScissor(m_CommandBuffers[frameInfo.ImageIndex]->Get(), 0, 1, &scissor);

		vkCmdDraw(m_CommandBuffers[frameInfo.ImageIndex]->Get(), 3, 1, 0, 0);

		frameInfo.RenderPass->End(m_CommandBuffers[frameInfo.ImageIndex]);
		m_CommandBuffers[frameInfo.ImageIndex]->EndRecording();
	}

	void SceneSys::load_shaders()
	{
		ENGINE_INFO("Default System: Loading Shaders");
		auto vert = GraphicsFactory::CreateShader("shaders/DefaultRSVert.glsl", VERTEX);
		auto frag = GraphicsFactory::CreateShader("shaders/DefaultRSFrag.glsl", FRAGMENT);

		m_Shaders.push_back(vert);
		m_Shaders.push_back(frag);
	}

	void SceneSys::create_pipeline()
	{
		ENGINE_INFO("Default System: Creating Pipeline");
		m_Pipeline = GraphicsFactory::CreatePipeline(m_Shaders);
	}
}