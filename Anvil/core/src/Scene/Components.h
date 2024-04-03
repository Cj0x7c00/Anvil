#pragma once
#include "../UUID/uuid.h"
#include "../UI/Canvas.h"
#include "glm/glm.hpp"
#include "entt/entt.hpp"
#include "../Renderer/UBO.h"
#include "../Renderer/Texture/Texture.h"
#include <string>
#include <vector>
#include <array>
#include "../Renderer/Renderer.h"

struct VkVertexInputBindingDescription;
struct VkVertexInputAttributeDescription;
typedef struct VkBuffer_T* VkBuffer;

namespace Anvil
{
	class Entity;

	/// <summary>
	/// Store the base Entity class pointer for the Entt system.
	/// makes it easier to find entities
	/// </summary>
	struct UserPointerComponent
	{
		Entity* entity;

		UserPointerComponent(Entity* _ent);
		
		/// <summary>
		/// Get the Anvil Entity handle from an entt entity
		/// </summary>
		/// <returns>Entity*</returns>
		Entity* Get();
	};

	/// <summary>
	/// Used for naming entities
	/// </summary>
	struct TagComponent
	{
		std::string tag;

		TagComponent(std::string _tag)
			: tag{_tag}
		{
		}

		/// <summary>
		/// Get the tag of the entity
		/// </summary>
		/// <returns>string</returns>
		std::string Get()
		{
			return tag;
		}
	};

	/// <summary>
	/// Universal Unique Identifire component. used to find a specific entity when 
	/// looking through the registry
	/// </summary>
	struct UUIDComponent
	{
		UuID uuid;

		UUIDComponent()
		{
			
		}

		/// <summary>
		/// Get the UUID of the entity
		/// </summary>
		/// <returns>string</returns>
		std::string Get()
		{
			return uuid.GetUUID();
		}
	};

	struct vertex
	{
		glm::vec2 position{};
		glm::vec3 color{};

		vertex(glm::vec2 _pos, glm::vec3 _col)
			: position{ _pos }, color{ _col }
		{

		}

		static VkVertexInputBindingDescription GetBindingDescription();

		static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();
	};

	/// <summary>
	/// Sprite component. holds data of the sprite in use for rendering
	/// </summary>
	struct SpriteComponent
	{
		std::vector<vertex>     verts{
			{{-0.5f , -0.5f}, {0.63, 0.63, 0.63}},
			{{0.5f  , -0.5f}, {0.63, 0.63, 0.63}},
			{{0.5f  ,  0.5f}, {0.63, 0.63, 0.63}},
			{{-0.5f ,  0.5f}, {0.63, 0.63, 0.63}}
		};
		std::vector<uint16_t>   indexs{
			0, 1, 2, 2, 3, 0
		};

		VkBuffer vertexBuffer = NULL;
		VkBuffer indexBuffer  = NULL;

		UniformBufferObject UBO = {};

		bool buffersCreatedFlag = false;

		SpriteComponent()
		{

		}

		SpriteComponent(Texture& text)
		{

		}

		void CreatBuffers();

		void Bind(CommandBuffer* cmdBuffer, Ref<Pipeline> pipeline);
		void Draw(CommandBuffer* cmdBuffer);
	};

	struct CanvasComponent
	{
		Ref<Canvas> canvas;

		CanvasComponent()
		{
			canvas = Canvas::Create();
		}

		Ref<Canvas> Get()
		{
			return canvas;
		}
	};
}