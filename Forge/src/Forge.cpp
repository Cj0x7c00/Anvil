#include "ForgeLayer.h"
#include <glm/glm.hpp>
#include "Anvil.hpp"
#include "core/src/Base/EntryPoint.hpp"

class Forge : public Anvil::AnvilApplication
{
public:
	SCENE  Scene;
	ENTITY Triangle;

	Forge(Anvil::AppProperties _p) : AnvilApplication(_p)
	{
		PushLayer(new ForgeLayer());
	}

	~Forge()
	{

	}

	void Awake() override
	{
		Scene = m_SceneManager.GetActiveScene();
		Triangle = Scene->CreateEntity("Triangle");

		std::vector<Anvil::vertex> verts =
		{
			{{0.0, -0.5}, {1.0, 0.0, 0.0}},
			{{0.5, 0.5}, {0.0, 1.0, 0.0}},
			{{-0.5, -0.5}, {0.0, 0.0, 1.0}}
		};

		auto Sprite = Triangle->AddComponent<Anvil::SpriteComponent>(verts);
	}

	void Update() override
	{

	}

	void LateUpdate() override
	{

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


