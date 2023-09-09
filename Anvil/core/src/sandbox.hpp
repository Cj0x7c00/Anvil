#include "Anvil.hpp"

namespace Anvil{
class SandboxAppLayer : public Anvil::AnvilLayer
{

    public: 
        int counter = 0;

    SandboxAppLayer();

    void Attach(); 
    void Update(Timestep ts); 
    void Detach();

};
}