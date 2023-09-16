#include "sandbox.hpp"
namespace Anvil{
SandboxAppLayer::SandboxAppLayer() : AnvilLayer("Sandbox App") {};

void SandboxAppLayer::Attach() 
{
    UUID uuid; // test UUID

    ENGINE_INFO("Sandbox Layer: " + uuid.GetUUID());

}
void SandboxAppLayer::Update(Timestep ts) 
{
    counter++;
    if (counter % 1000 == 0){
        ENGINE_INFO("Time: " + std::to_string(ts.GetMilliseconds()) + "ms");
    }
}
void SandboxAppLayer::Detach() 
{
    ENGINE_INFO("Sandbox Layer: ");
}
}