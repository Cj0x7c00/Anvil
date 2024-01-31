#pragma once
#include "../UUID/uuid.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>


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
	};

	struct SpriteComponent
	{
		std::vector<vertex> verts;
	
		SpriteComponent(std::vector<vertex> _vert)
			: verts{ _vert }
		{
		
		};
	};
}