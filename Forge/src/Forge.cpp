#include "Anvil.hpp"

class Forge : public Anvil::AnvilApplication
{
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