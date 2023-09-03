#include "sandbox.hpp"
namespace Anvil{
SandboxAppLayer::SandboxAppLayer() : AnvilLayer("Sandbox App") {};

void SandboxAppLayer::Attach() 
{
    ENGINE_INFO("Sandbox Layer: ", "Attach");

    
}

void SandboxAppLayer::Update(Timestep ts) 
{
    counter++;
    if (counter % 500 == 0){
        ENGINE_INFO("Time: " + std::to_string(ts.GetMilliseconds()) + "ms", "Update");
    }


}

void SandboxAppLayer::Detach() 
{
    ENGINE_INFO("Sandbox Layer: ", "Detach");
}
}