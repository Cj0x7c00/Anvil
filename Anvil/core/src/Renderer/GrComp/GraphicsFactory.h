#pragma once
#include <vector>

#include "../../Base/Pointer.hpp"
#include "../../Base/macros.hpp"
#include "Shader.h"

namespace Anvil
{

	class Pipeline;
	class Shader;

	/// <summary>
	/// Graphics factory for creating shaders, pipelines, ond others
	/// </summary>
	class ANV_API GraphicsFactory
	{
	public:
		/// <summary>
		/// Create a pipeline 
		/// </summary>
		/// <param name="_shaders">vector of anvil shaders</param>
		/// <returns>Ref of the new pipeline</returns>
		static Ref<Pipeline> CreatePipeline(std::vector<Ref<Shader>> _shaders);

		/// <summary>
		/// Create a anvil shader 
		/// </summary>
		/// <param name="_file_path">path to the shader</param>
		/// <param name="_t">shader type</param>
		/// <param name="_od">out directory (optional)</param>
		/// <returns>Ref of the new shader</returns>
		static Ref<Shader> CreateShader(const char* _file_path, ShaderType _t, const char* _od="");

	};
}

