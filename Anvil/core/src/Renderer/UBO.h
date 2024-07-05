#pragma once

#include <glm/glm.hpp>

namespace Anvil
{
    struct PushConstantData
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
        glm::vec3 color;
        float padding;
    };

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };
}