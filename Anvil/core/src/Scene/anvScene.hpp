#include "../Anvil.hpp"
#include "../include/entt/single_include/entt/entt.hpp"

namespace Anvil
{
    class Entity;

    class Scene
    {
        public:

          Entity CreateEntity();
          Entity CopyEntity();

          void DestroyEntity();

        private:
          entt::registry m_Registry;

          friend class Entity;
          
    };
}