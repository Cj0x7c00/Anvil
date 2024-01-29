#include "ForgeLayer.h"

#include "core/src/Base/EntryPoint.hpp"

class Forge : public Anvil::AnvilApplication
{
public:
	Forge(Anvil::AppProperties _p) : AnvilApplication(_p)
	{
		PushLayer(new ForgeLayer());
	}

	~Forge()
	{
		
	}

	void Run() override
	{
        while (!GetWindow()->ShouldClose()) {

            GetWindow()->PollEvents();
			Anvil::Renderer::NewFrame();
        }
		Anvil::Renderer::WaitIdle();
	}
};

// Entry point
Anvil::AnvilApplication* Anvil::CreateApplication()
{
	AppProperties props;
	props.win_props.name = "Forge Editor";
	props.win_props.width = 1000;
	props.win_props.height = 900;

	ANVIL_DEBUG("Work Dir: {}", props.wrkdir);
	return new Forge(props);
}


