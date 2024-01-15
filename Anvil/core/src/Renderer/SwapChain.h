#pragma once
#include "Devices.h"

namespace Anvil
{
	class SwapChain
	{
	public:
		static Ref<SwapChain> Create();
		SwapChain() : m_Devices{Devices::GetInstance()}
		{
			ENGINE_DEBUG("Creating Swap Chain");
			create_swap_chain();
			create_image_views();
			
		}
		~SwapChain() {}

	private:
		void create_swap_chain();
		void create_image_views();

	private:
		VkSwapchainKHR			 m_SwapChain;
		std::vector<VkImage>	 m_SwapChainImages;
		std::vector<VkImageView> m_SwapChainImageViews;
		Ref<Devices>			 m_Devices;

		VkFormat   m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;

	};
}
