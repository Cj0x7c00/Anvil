#include "sandbox.hpp"
#include "../Anvil/core/src/EntryPoint.hpp"
namespace Anvil{

class sandboxapp : public AnvilApplication
{
    public:
        AnvilApplication* app;

        sandboxapp() : AnvilApplication()
        {
            PushLayer(new SandboxAppLayer());
        }

        ~sandboxapp() {}
};


AnvilApplication* CreateApplication()
{
    return new sandboxapp();
}

}