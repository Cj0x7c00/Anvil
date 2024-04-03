#pragma once
#include "string"
#include "../../Base/Pointer.hpp"
#include "../Renderer.h"

typedef struct VkImage_T* VkImage;
typedef struct VkBuffer_T* VkBuffer;
typedef struct VkDeviceMemory_T* VkDeviceMemory;
typedef struct VkImageView_T* VkImageView;
enum VkFormat;
enum VkImageLayout;


namespace Anvil
{
	class Texture
	{
	public:
		
		static Ref<Texture> Create(std::string _file);

		Texture(std::string _fp) : m_FilePath{_fp}
		{
			create_texture_image();
		}

	public:
		int Tiling = 1;

	private:
		void create_texture_image();
		void layout_transition(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		void copy_buffer_to_img(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	private:
		std::string m_FilePath;

		VkImage         m_Image;
		VkImageView		m_View;
		VkDeviceMemory  m_ImgMem;
	};
}
