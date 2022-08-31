#pragma once
#include "anvpch.hpp"
#include "anvDevice.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace Anvil
{
    class anvModel
    {
        public:

            struct Vertex
            {
                glm::vec3 position{1.f};
                glm::vec3 color;
                
                static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
                static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
            };

            anvModel(AnvDevice &device, const std::vector<Vertex> &vertices);
            ~anvModel();

            anvModel(const anvModel &) = delete;
            anvModel &operator=(const anvModel &) = delete;

            void Bind(VkCommandBuffer cmdBuffer);
            void Draw(VkCommandBuffer cmdBuffer);

            private:
                void CreateVertexBuffer(const std::vector<Vertex> &vertices);

                AnvDevice &anvDevice;
                VkBuffer vertexBuffer;
                VkDeviceMemory vertexBufferMemory;
                uint32_t vertCount;
    };
}