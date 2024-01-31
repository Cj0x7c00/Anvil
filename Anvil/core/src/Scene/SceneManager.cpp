#include "SceneManager.h"

std::vector<Anvil::Ref<Anvil::Scene>> Anvil::SceneManager::m_Scenes = {};
int Anvil::SceneManager::m_InsertIndex = 0;

namespace Anvil
{
	void SceneManager::NewSceneCreated(Ref<Scene> _new)
	{
		Emplace(_new);
		ENGINE_DEBUG("Scenes created: {}", m_Scenes.size());
	}

	Ref<Scene> SceneManager::GetActiveScene()
	{
		return m_ActiveScene;
	}

	void SceneManager::SetActiveScene(Ref<Scene> _scene)
	{
		m_ActiveScene = _scene;
	}

	void SceneManager::Emplace(Ref<Scene> _scene)
	{
		m_Scenes.emplace(m_Scenes.begin() + m_InsertIndex, _scene);
		m_InsertIndex++;
	}
	 
	void SceneManager::Delete(Ref<Scene> _scene)
	{
		auto it = std::find(m_Scenes.begin(), m_Scenes.begin() + m_InsertIndex, _scene);
		if (it != m_Scenes.begin() + m_InsertIndex)
		{
			m_Scenes.erase(it);
			m_InsertIndex--;
		}
	}
}