#pragma once
#include "../Devices.h"

namespace Anvil
{
	enum ShaderType {
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		TESSELATION
	};

	class Shader
	{
	public:
		static Scope<Shader> Create(const char* _file_path, ShaderType _t);

		Shader(const char* _file_path, ShaderType _t)
		{

		}

		~Shader() {};
	private:
		const char* m_Source;
		ShaderType m_Type;
	};
}

// somthing like this maybe later on ...
//#define SHADER_UTIL_ADD_INCLUDE_DIR(...) Shader::AddIncludeDir(__VA_ARGS__); 
