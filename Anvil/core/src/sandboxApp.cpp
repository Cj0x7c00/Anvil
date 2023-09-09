#include "sandbox.hpp"
#include "EntryPoint.hpp"
namespace Anvil{
class sandboxapp : public Anvil::AnvilApplication
{
    public:
        sandboxapp() : Anvil::AnvilApplication()
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