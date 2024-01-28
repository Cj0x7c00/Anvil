#pragma once
#include "../Base/Pointer.hpp"
#include "../Scene/Scene.h"
#include "RenderPass.h"
#include "CommandBuffer.h"
#include <vector>

namespace Anvil
{

	class SwapChain;

	class RenderSystem
	{
	public:
		static Ref<RenderSystem> Default(Ref<SwapChain> _sc);

		RenderSystem(Ref<SwapChain> _sc);

		virtual void Init() = 0;
		virtual void NewFrame(Ref<RenderPass> renderPass, Ref<Scene> scene) = 0;
		virtual void NewFrame(Ref<RenderPass>, uint32_t imageIndex) = 0;

		void Flush(uint32_t imageIndex);
		Ref<CommandBuffer> GetCommandBuffer(uint32_t imageIndex);

		void WindowWasResized(Ref<SwapChain> _sc);

	protected:
		std::vector<Ref<CommandBuffer>> m_CommandBuffers;
		Ref<SwapChain>  m_SwapChain;

		
	};
}