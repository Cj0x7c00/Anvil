#pragma once
#include "../../Base/Pointer.hpp"
#include "../../Base/macros.hpp"
#include <string>
//#include <vulkan/vulkan.h>
// indirectly link to the struct
typedef struct VkShaderModule_T* VkShaderModule;
typedef struct VkPipelineShaderStageCreateInfo;
enum VkShaderStageFlagBits;

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

		Shader(const char* _file_path, ShaderType _t, const char* _od="")
			: m_Source{_file_path}, m_Type{_t}, m_OutDir{_od}
		{
			compile();
			make_module();
		}

		~Shader() {};

		std::string GetName() { return m_CompFile; };

		VkShaderModule& GetModule();
		ShaderType GetType();
		VkShaderStageFlagBits GetStage();


	private:
		void compile();
		void make_module();

		std::string get_dir(std::string dir);
		std::string enum_t_to_str(ShaderType t);
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
