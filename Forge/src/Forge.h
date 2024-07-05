#pragma once
#include "ForgeLayer.h"
#include <glm/glm.hpp>
#include "Anvil.hpp"
#include "core/src/Base/EntryPoint.hpp"

class Forge : public Anvil::AnvilApplication
{
public:

	Forge(Anvil::AppProperties _p) : AnvilApplication(_p)
	{
		
	}

	~Forge()
	{

	}

	void Awake() override;

	void Update() override;


	void LateUpdate() override
	{

	}
};

// Entry point
Anvil::AnvilApplication* Anvil::CreateApplication()
{
	AppProperties props;
	props.win_props.name = "Forge Editor";
	//props.win_props.width = 1300;
	//props.win_props.height = 700;
	
	props.win_props.maximized = true;

	props.wrkdir = std::filesystem::current_path().string();
	ANVIL_DEBUG("Work Dir: {}", props.wrkdir);
	return new Forge(props);
}



