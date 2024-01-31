#include "Components.h"
#include <vulkan/vulkan.h>
#include "Entity.h"

namespace Anvil
{
	UserPointerComponent::UserPointerComponent(Entity* _ent) 
		: entity{ _ent }
	{

	}

	Entity* UserPointerComponent::Get()
	{
		return entity;
	}

	VkVertexInputBindingDescription vertex::GetBindingDescription() 
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	std::array<VkVertexInputAttributeDescription, 2> vertex::GetAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(vertex, color);
		return attributeDescriptions;
	}


}