#include "Shader.h"

namespace Anvil
{
    Scope<Shader> Shader::Create(const char* _file_path, ShaderType _t)
    {
        ENGINE_INFO("[VK] Creating Shader: {}", _file_path);
        return CreateScope<Shader>(_file_path, _t);
    }
}
