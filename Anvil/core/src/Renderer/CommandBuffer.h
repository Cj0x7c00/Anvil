#pragma once

#include "../Base/Pointer.hpp"

typedef struct VkCommandBuffer_T* VkCommandBuffer;

namespace Anvil
{
	class CommandBuffer
	{
	public:
		static Ref<CommandBuffer> Create();

		CommandBuffer()
		{
			create_cmd_buffer();
		}

		VkCommandBuffer& Get();

		void BeginRecording();
		void EndRecording();
		void Reset();

	private:
		void create_cmd_buffer();

	private:
		VkCommandBuffer m_CommandBuffer;
	};
}

