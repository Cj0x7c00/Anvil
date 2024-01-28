#pragma once
#include "Devices.h"
#include "../core/src/Util/anvLog.hpp"


namespace Anvil
{
	class SwapChain
	{
	public:
		static Ref<SwapChain> Create();
		static Ref<SwapChain> Create(Extent2D _ext);

		SwapChain() : m_Devices{ Devices::GetInstance() }
		{
			ENGINE_DEBUG("Creating Swap Chain");
			create_swap_chain();
			create_image_views();
			
		}

		SwapChain(Extent2D _ext) : m_Devices{ Devices::GetInstance() }
		{
			ENGINE_DEBUG("Creating Swap Chain");
			create_swap_chain(_ext);
			create_image_views();

		}

		~SwapChain() {}

		void CreateFrameBuffers(VkRenderPass& _rp);

		VkFormat GetFormat()						  { return m_SwapChainImageFormat;  }
		std::vector<VkFramebuffer>& GetFrameBuffers() { return m_SwapChainFramebuffers; }
		std::vector<VkImageView>& GetImageViews() { return m_SwapChainImageViews; }
		VkExtent2D	GetExtent()		   { return m_SwapChainExtent; }
		VkSwapchainKHR& GetSwapChain() { return m_SwapChain; }

	private:
		void create_swap_chain();
		void create_swap_chain(Extent2D _ext);
		void create_image_views();

	private:
		std::vector<VkImage>	   m_SwapChainImages;
		std::vector<VkImageView>   m_SwapChainImageViews;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers;
		Ref<Devices>			   m_Devices;

		VkSwapchainKHR m_SwapChain;
		VkFormat       m_SwapChainImageFormat;
		VkExtent2D	   m_SwapChainExtent;
		VkRenderPass   m_RenderPass;
	};
}
