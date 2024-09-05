#pragma once
#include <glm/glm.hpp>
#include "Anvil.hpp"
#include "core/src/Base/EntryPoint.hpp"

class Jump : public Anvil::AnvilApplication
{
public:

	Jump(Anvil::AppProperties _p) : AnvilApplication(_p)
	{
	}

	~Jump()
	{

	}

	void Awake() override;

	void Update() override;


	void LateUpdate() override
	{

	}

	Anvil::Ref<Anvil::Canvas> m_Canvas;
};

// Entry point
Anvil::AnvilApplication* Anvil::CreateApplication()
{
	AppProperties props;
	props.win_props.name = "Your Game";
	//props.win_props.width = 1300;
	//props.win_props.height = 700;
	
	props.win_props.maximized = true;

	props.wrkdir = std::filesystem::current_path().string();
	ANVIL_DEBUG("Work Dir: {}", props.wrkdir);
	return new Jump(props);
}



