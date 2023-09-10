#include "../Anvil/core/src/Anvil.hpp"

namespace Anvil{
class SandboxAppLayer : public AnvilLayer
{

    public: 
        int counter = 0;

    SandboxAppLayer();

    virtual void Attach() override; 
    virtual void Update(Timestep ts) override; 
    virtual void Detach() override;

};
}