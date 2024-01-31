#include "GraphicsFactory.h"
#include "Pipeline.h"

#include "../Renderer.h"

namespace Anvil
{
	Ref<Pipeline> GraphicsFactory::CreatePipeline(std::vector<Ref<Shader>> _shaders)
	{
		return Pipeline::Create(_shaders);
	}

	Ref<Shader> GraphicsFactory::CreateShader(const char* _file_path, ShaderType _t, const char* _od)
	{
		return Shader::Create(_file_path, _t, _od);
	}
}