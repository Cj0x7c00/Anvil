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

}
void SandboxAppLayer::Detach() 
{
    ENGINE_INFO("Sandbox Layer: ");
}
}