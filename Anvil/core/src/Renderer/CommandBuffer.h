#pragma once

#include "../Base/Pointer.hpp"
#include "Renderer.h"

typedef struct VkCommandBuffer_T* VkCommandBuffer;

namespace Anvil
{
	class Pipeline;
	class RenderPass;

	struct NewFrameInfo;

	class CommandBuffer
	{
	public:
		static Ref<CommandBuffer> Create();

		CommandBuffer()
		{
			create_cmd_buffer();
		}

		VkCommandBuffer& Get();

		void BeginRecording(NewFrameInfo& _fi, Ref<Pipeline> _pipeline);
		void BeginRecording();
		void EndRecording(NewFrameInfo& _fi);
		void EndRecording();
		void Reset();

	private:
		void create_cmd_buffer();

	private:
		VkCommandBuffer m_CommandBuffer;
	};
}

