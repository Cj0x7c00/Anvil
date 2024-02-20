/*
* Scene View Pannel
* 
* the scene view is where you can see all the entities and their 
* children within the active scene. you can also add/remove entities as 
* you wish
* 
*/

#pragma once
#include <Anvil.hpp>

using namespace Anvil;

class SceneView
{
public:
	SceneView(Anvil::SceneManager& SceneManager, Ref<Canvas> Canvas)
		: m_SceneManager{SceneManager}, m_Canvas{Canvas}
	{
		Init();
	}

private:
	void Init();
	void DrawEntities();
	void DrawUI();

private:
	Anvil::SceneManager& m_SceneManager;
	Ref<Canvas> m_Canvas;
	SCENE m_activeScene;
};

