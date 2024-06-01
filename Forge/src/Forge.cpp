#include "Forge.h"
#include <core/src/Scene/Components.h>

void Forge::Awake() 
{

	PushLayer(new ForgeLayer(m_SceneManager));
}

void Forge::Update()
{

}