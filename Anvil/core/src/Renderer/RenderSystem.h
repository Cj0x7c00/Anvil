#pragma once
#include "../Base/Pointer.hpp"
#include "../Scene/Scene.h"
#include "RenderPass.h"
#include "CommandBuffer.h"

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

		void Flush();
		Ref<CommandBuffer> GetCommandBuffer();

	protected:
		Ref<CommandBuffer> m_CommandBuffer;
		Ref<SwapChain>  m_SwapChain;
	};
}