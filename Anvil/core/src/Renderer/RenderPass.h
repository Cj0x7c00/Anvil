#pragma once
#include "../Base/Pointer.hpp"

typedef struct VkRenderPass_T* VkRenderPass;
typedef struct  VkRenderPassBeginInfo;


namespace Anvil
{
	class SwapChain;
	class CommandBuffer;

	class RenderPass
	{
	public:
		static Ref<RenderPass> Create(Ref<SwapChain> _sc);

		RenderPass(Ref<SwapChain> _sc)
			: m_SwapChain{_sc}
		{
			create_pass();
		}

		void Begin(Ref<CommandBuffer> _cmdBuffer, uint32_t imgIndex);
		void End(Ref<CommandBuffer> _cmdBuffer);

		VkRenderPass& Get();
		void WindowWasResized(Ref<SwapChain> _new);
	private:
		void create_pass();

	private:
		Ref<SwapChain> m_SwapChain;

		VkRenderPass			m_RenderPass;
	};
}

