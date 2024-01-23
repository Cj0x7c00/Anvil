#include "RenderSystem.h"
#include "DefaultSystem/defaultRS.h"

namespace Anvil
{
	Ref<RenderSystem> RenderSystem::Default()
	{
		return CreateRef<defaultRS>();
	}
}
