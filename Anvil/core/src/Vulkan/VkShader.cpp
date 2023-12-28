#include "VkShader.h"
#include <string>
#include <algorithm>

namespace Anvil
{

	void ShaderUtility::remove_white(std::string& str)
	{
		std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
		std::string::iterator end_poss = std::remove(str.begin(), str.end(), '\n');
		str.erase(end_pos, str.end());
		str.erase(end_poss, str.end());
	}

	std::string ShaderUtility::make_type_string(ShaderType t)
	{
		switch (t)
		{
		case Anvil::VERTEX:
			return "vertex";
			break;
		case Anvil::FRAGMENT:
			return "fragment";
			break;
		case Anvil::TESSELATION:
			break;
		case Anvil::GEOMETRY:
			break;
		default:
			break;
		}
	}
	

	Ref<VkShader> VkShader::Create(std::string file, ShaderType t, std::string o)
	{
		return CreateRef<VkShader>(file, t, o);
	}

	VkShader::VkShader(std::string file, ShaderType t, std::string o)
		: m_FilePath{file}, m_Type{t}, m_OutDir{o}
	{
		_Compile();
		_MakeModule();
	}

	void VkShader::_Compile()
	{
		auto VK_SDK = TaskRunner::Execute("echo %VULKAN_SDK%");
		ShaderUtility::remove_white(VK_SDK);
		auto _ts = ShaderUtility::make_type_string(m_Type);
		ENGINE_DEBUG("{}", VK_SDK);
		ENGINE_DEBUG("Shader Type: {}", _ts);
		ENGINE_DEBUG("{}", std::filesystem::current_path());
		m_FileName = m_FilePath + ".spv";

		std::stringstream cmd;
		cmd << VK_SDK << "\\Bin\\glslc " << "-fshader-stage=" << _ts << " " << m_FilePath << " -o " << m_FileName;
		ENGINE_DEBUG("{}", cmd.str());
		TaskRunner::Execute(cmd.str().c_str());
	}

	void VkShader::_MakeModule()
	{
		// Read Compiled Output
		std::ifstream file(m_FileName, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			ENGINE_WARN("Failed to read file: {}", m_FileName);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();

		VkShaderModuleCreateInfo modinfo;
		modinfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		modinfo.codeSize = buffer.size();
		modinfo.flags = 0;
		modinfo.pCode = reinterpret_cast<const uint32_t*>(buffer.data());

		auto res = vkCreateShaderModule(AnvDevice::GetInstance()->m_device, &modinfo, nullptr, &m_Module);

		if (res != VK_SUCCESS)
		{
			ENGINE_WARN("Failed to create shader module: {}", m_FileName);
		}
	}
}