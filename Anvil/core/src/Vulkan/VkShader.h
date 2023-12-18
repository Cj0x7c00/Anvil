#pragma once

#include "anvDevice.hpp"
#include "../Util/TaskRunner/TaskRunner.h"
#include "../Pointer.hpp"

namespace Anvil
{

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		TESSELATION,
		GEOMETRY
	};

	struct ShaderUtility
	{
		static void remove_white(std::string& str);

		static std::string make_type_string(ShaderType t);
	};

	class VkShader 
	{
	public:
		/// <summary>
		/// Creates a shader for anvil to use from a scource file
		/// </summary>
		/// <param name="file">path to file</param>
		/// <param name="t">shader type</param>
		/// <param name="o">output dir</param>
		/// <returns>reference handle to the anvil shader</returns>
		static Ref<VkShader> Create(std::string file, ShaderType t, std::string o = "");

		// Getters
		
		/// <summary>
		/// Get the shader file 
		/// </summary>
		/// <returns></returns>
		std::string GetFilePath() {};
		std::string GetFileName() {};
		ShaderType GetType() {};
		VkShaderModule& GetModule() { return m_Module; };

		~VkShader() {};
		VkShader(std::string file, ShaderType t, std::string o);
	private:

		void _Compile();
		void _MakeModule() ;

	private:
		std::string     m_FilePath;
		std::string     m_FileName;
		std::string     m_OutDir;
		ShaderType      m_Type;
		VkShaderModule  m_Module;
	};

	using SHADER = Ref<VkShader>;
}
