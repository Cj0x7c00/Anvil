/*****************************************************
* 
* Vulkan specific stuff
* Sets up everything required to operate with vulkan
* 
* singleton
* 
******************************************************/

#pragma once
#include "../Util/anvLog.hpp"
#include "../Base/Pointer.hpp"
#include "../Window/Window.hpp"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>	
#include <optional>

namespace Anvil
{
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class Devices
	{
	public:

		Devices(Ref<Window> win) : m_Window{win}
		{
			ENGINE_DEBUG("[VK] Devices instantiated");
			m_Surface = (VkSurfaceKHR)m_Window->GetSurface(); // works for now
			create_instance();
			create_surface();
			select_gpu();
			logical_setup();
			create_command_pool();
		}

		~Devices()
		{
			
		}

		static Ref<Devices> Init(Ref<Window> window);
		static Ref<Devices> GetInstance() { return m_This; }

		// Getters //
		VkInstance&       Instance();
		VkPhysicalDevice& GPU();
		VkDevice&         Device();
		VkSurfaceKHR&	  Surface();
		VkCommandPool&    CommandPool();

		// API //
		SwapChainSupportDetails QuerySwapChainSupport();
		VkSurfaceFormatKHR		ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR		ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D				ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		QueueFamilyIndices		FindQueueFamilies(VkPhysicalDevice dev);
		VkQueue& GraphicsQueue() { return m_GraphicsQueue; };
		VkQueue& PresentQueue() { return m_PresentQueue; };

	private:
		void create_instance();
		void select_gpu();
		void logical_setup();
		void create_surface();
		void create_command_pool();
		bool check_layer_support();
		bool check_devEXT_support(VkPhysicalDevice dev);
		int  rate_device_suitability(VkPhysicalDevice dev);
		SwapChainSupportDetails  query_sc_support(VkPhysicalDevice dev);
		std::vector<const char*> get_extensions();

	private:
		// class instance ref
		static Ref<Devices> m_This;
		Ref<Window>		    m_Window;

		VkInstance		 m_Instance;
		VkPhysicalDevice m_GPU = VK_NULL_HANDLE;
		VkDevice		 m_Device = VK_NULL_HANDLE;
		VkQueue			 m_GraphicsQueue;
		VkQueue			 m_PresentQueue;
		VkSurfaceKHR	 m_Surface;
		VkCommandPool    m_CommandPool;

		std::vector<const char*> m_DeviceExt = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

#ifdef DEBUG
		std::vector<const char*> m_ValidationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		const bool m_ValidationEnabled = true;
#else
		std::vector<const char*> m_ValidationLayers = {};
		const bool m_ValidationEnabled = false;
#endif

	};

}