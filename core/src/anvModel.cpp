#include "anvModel.hpp"
#include <cassert>
#include <cstring>

namespace AnvilEngine
{
    anvModel::anvModel(AnvDevice &device, const std::vector<Vertex> &vertices) : anvDevice{device}{
        CreateVertexBuffer(vertices);
    }

    anvModel::~anvModel()
    {
        vkDestroyBuffer(anvDevice.m_device, vertexBuffer, nullptr);
        vkFreeMemory(anvDevice.m_device, vertexBufferMemory, nullptr);
    }

    void anvModel::CreateVertexBuffer(const std::vector<Vertex> &vertices)
    {
        vertCount = static_cast<uint32_t>(vertices.size());
        assert(vertCount >=3 && "Vertex count must be at least 3");
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertCount;

        anvDevice.CreateBuffer(
            bufferSize, 
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            vertexBuffer,
            vertexBufferMemory);

        void *data;
        vkMapMemory(anvDevice.m_device, vertexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(anvDevice.m_device, vertexBufferMemory);
    }

    void anvModel::Bind(VkCommandBuffer cmdBuffer)
    {
        VkBuffer buffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(cmdBuffer, 0, 1, buffers, offsets);
    }

    void anvModel::Draw(VkCommandBuffer cmdBuffer)
    {
        vkCmdDraw(cmdBuffer, vertCount, 1, 0, 0);
    }

    std::vector<VkVertexInputBindingDescription> anvModel::Vertex::GetBindingDescriptions()
    {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> anvModel::Vertex::GetAttributeDescriptions(){
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(1);

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = 0;
        return attributeDescriptions;
    }
}