

#include "ForgeLayer.h"

#include "core/src/Base/EntryPoint.hpp"

class Forge : public Anvil::AnvilApplication
{
public:
	Forge()
	{
		PushLayer(new ForgeLayer());
	}

	void Run() override
	{
        while (!GetWindow()->ShouldClose()) {

            GetWindow()->PollEvents();
        }
	}
};

// Entry point
Anvil::AnvilApplication* Anvil::CreateApplication()
{
	return new Forge();
}