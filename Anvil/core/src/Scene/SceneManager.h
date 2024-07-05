#pragma once
#include "../Base/Pointer.hpp"
#include "../Base/macros.hpp"
#include "Scene.h"

namespace Anvil
{
	class ANV_API SceneManager
	{
	public:
		SceneManager()
		{
			m_ActiveScene = Scene::Create("New Scene");
		}

		static void NewSceneCreated(Ref<Scene> _new);
		static Ref<Scene> GetActiveScene();
		void SetActiveScene(Ref<Scene> _scene);

		static void Emplace(Ref<Scene> _scene);
		void Delete(Ref<Scene> _scene);

	private:
		static int m_InsertIndex;
		static Ref<Scene> m_ActiveScene;
		static std::vector<Ref<Scene>> m_Scenes;
	};
}

