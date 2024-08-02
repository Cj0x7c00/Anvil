#pragma once
#include "RenderPass.h"
#include "CommandBuffer.h"
#include "../Scene/Scene.h"
#include "../Base/Pointer.hpp"
#include <vector>

#include <vulkan/vulkan.h>


namespace Anvil
{
	struct NewFrameInfo;
	class SwapChain;

	class RenderSystem
	{
	public:
		static std::vector<Ref<RenderSystem>> Default(Ref<SwapChain> _sc);
		static std::vector<RenderSystem*> GetSystems() { return m_SystemsInPlace; }

		RenderSystem(Ref<SwapChain> _sc);

		/// <summary>
		/// Called right after construction
		/// </summary>
		virtual void Init() = 0;

		/// <summary>
		/// Called only once after the initial command buffer recording.
		/// use for single time commands.
		/// </summary>
		virtual void OnCallOnce(CommandBuffer cmdBuffer);


		/// <summary>
		/// Called before rendering begins.
		/// </summary>
		virtual void Update(NewFrameInfo& frameInfo);

		/// <summary>
		/// main process function. called once per frame.
		/// </summary>
		/// <param name="frameInfo">All the information needed for frame rendering</param>
		virtual void NewFrame(NewFrameInfo& frameInfo) = 0;
		

		/// <summary>
		/// Define custom behaviour if the window wasresized
		/// </summary>
		/// <param name="_sc">Swap Chain</param>
		static void WindowWasResized(Ref<SwapChain> _sc);


	protected:
		static Ref<SwapChain>  m_SwapChain;

	private:
		static std::vector<RenderSystem*> m_SystemsInPlace;
	};
}