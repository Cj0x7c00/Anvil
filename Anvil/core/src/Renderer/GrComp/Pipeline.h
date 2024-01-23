#pragma once
#include "../../Base/Pointer.hpp"
#include "../../Base/macros.hpp"
#include "Shader.h"
#include <vector>
#include <vulkan/vulkan.h>

namespace Anvil
{
    class ANV_API Pipeline
    {
    public:
        static Ref<Pipeline> Create(std::vector<Ref<Shader>> _shaders);

        Pipeline(std::vector<Ref<Shader>> _shaders);

        ~Pipeline();

    private:
        void process_shaders(std::vector<Ref<Shader>> _shaders);
        void create_pipeline_layout();

    private:
        VkPipeline       m_Pipeline;
        VkPipelineLayout m_Layout;

        std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages;
    };
}

