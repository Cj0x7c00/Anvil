#pragma once
#include "../../Base/Pointer.hpp"
#include "../../Base/macros.hpp"
#include <shaderc/shaderc.hpp>
#include <string>
#include <vulkan/vulkan.h>


namespace Anvil
{	
	enum ShaderType {
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		TESSELATION
	};

	class ANV_API Shader
	{
	public:
		static Ref<Shader> Create(const char* _file_path, ShaderType _t, const char* _od="");

		Shader(const char* _file_path, ShaderType _t)
			: m_Source{ _file_path }, m_Type{ _t }, m_OutDir{ "" }
		{
			compile();
			make_module();
		}

		~Shader() {};

		std::string GetName() { return m_Source; };

		VkShaderModule& GetModule();
		ShaderType GetType();
		VkShaderStageFlagBits GetStage();


	private:
		void compile();
		void make_module();

		std::string get_dir(std::string dir);
		std::string enum_t_to_str(ShaderType t);
		shaderc_shader_kind enum_t_to_kind(ShaderType t);

	private:
		std::string    m_Source;
		std::string    m_CompFile;
		std::string    m_OutDir;
		ShaderType     m_Type;
		VkShaderModule m_Module;
	};
}

// something like this maybe later on ...
// tell the shader to look for shader paths. 
//#define SHADER_UTIL_ADD_INCLUDE_DIR(...) Shader::AddIncludeDir(__VA_ARGS__); 
