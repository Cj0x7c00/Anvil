#include "Shader.h"
#include "Util/TaskRunner/TaskRunner.h"
#include "../Devices.h"
#include <vulkan/vulkan.h>
#include <filesystem>
#include <sstream>

namespace Anvil
{
    std::string Shader::get_dir(std::string dir)
    {


        //char buffer[MAX_PATH];
        //GetModuleFileName(NULL, buffer, MAX_PATH);
        //std::string::size_type pos = std::string(buffer).find_last_of("\\/");
        //return std::string(buffer).substr(0, pos);
        return "";
        
    }

    std::string Shader::enum_t_to_str(ShaderType t)
    {
        switch (t)
        {
        case Anvil::VERTEX:
            return "vertex";
            break;
        case Anvil::FRAGMENT:
            return "fragment";
            break;
        case Anvil::GEOMETRY:
            return "geometry";
            break;
        case Anvil::TESSELATION:
            return "tesselation";
            break;
        default:
            break;
        }
    }

    Ref<Shader> Shader::Create(const char* _file_path, ShaderType _t, const char* _od)
    {
        ENGINE_INFO("[VK] Creating Shader: {}", _file_path);
        return CreateRef<Shader>(_file_path, _t);
    }
    VkShaderModule& Shader::GetModule()
    {
        return m_Module;
    }
    ShaderType Shader::GetType()
    {
        return m_Type;
    }
    void Shader::compile()
    {
        ENGINE_DEBUG("Compiling shader: {}", m_Source);
        auto _ty = enum_t_to_str(m_Type);
        std::stringstream cmd;
        cmd << VULKAN_SDK;
        cmd << "/bin/glslc ";
        cmd << " -fshader-stage=";
        cmd << _ty;
        cmd << " ";
        cmd << m_Source;
        cmd << " -o ";
        cmd << m_OutDir;

        m_CompFile = m_Source + ".spv";

        cmd << m_CompFile;
            
        TaskRunner::Execute(cmd.str().c_str()); // compile command execution
        
        ENGINE_INFO("Compiled Shader: {}", m_Source);
    }
    void Shader::make_module()
    {
        std::ifstream file(m_CompFile, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            ENGINE_WARN("Could not open shader file: {}", m_CompFile);
        }

        // read file
        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = buffer.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(buffer.data());
        if (vkCreateShaderModule(Devices::GetInstance()->Device(), &createInfo, nullptr, &m_Module) != VK_SUCCESS) {
            ENGINE_WARN("Failed to create shader module: {}", m_CompFile);
        }

        ENGINE_INFO("Created shader module for: {} ({})", m_Source, m_CompFile);
    }

    VkShaderStageFlagBits Shader::GetStage()
    {
        switch (m_Type)
        {
        case VERTEX:
            return VK_SHADER_STAGE_VERTEX_BIT;
            break;
        case FRAGMENT:
            return VK_SHADER_STAGE_FRAGMENT_BIT;
            break;
        case GEOMETRY:
            return VK_SHADER_STAGE_GEOMETRY_BIT;
            break;
        case TESSELATION:
            return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
            break;
        default:
            ENGINE_WARN("No shader type for {} found. vertex assumed", m_CompFile);
            return VK_SHADER_STAGE_VERTEX_BIT;
            break;
        }
    }
}
