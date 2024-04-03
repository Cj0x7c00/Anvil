#pragma once
#include "../Base/Pointer.hpp"

typedef struct VkRenderPass_T* VkRenderPass;
typedef struct  VkRenderPassBeginInfo;


namespace Anvil
{
	class CommandBuffer;
	class SwapChain;

	class RenderPass
	{
	public:
		static Ref<RenderPass> Create(Ref<SwapChain> _sc);

		RenderPass(Ref<SwapChain> _sc)
			: m_SwapChain{_sc}
		{
			create_pass();
		}

		void Begin(CommandBuffer* _cmdBuffer, uint32_t imgIndex);
		void End(CommandBuffer* _cmdBuffer);

		VkRenderPass& Get();
		void WindowWasResized(Ref<SwapChain> _new);
	private:
		void create_pass();

	private:
		Ref<SwapChain> m_SwapChain;

		VkRenderPass			m_RenderPass;
	};
}

