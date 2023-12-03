#include "sandbox.hpp"
namespace Anvil{
SandboxAppLayer::SandboxAppLayer() : AnvilLayer("Sandbox App") {};

void SandboxAppLayer::Attach() 
{
    ENGINE_INFO("Sandbox Layer: ", "Attach");
}
void SandboxAppLayer::Update(Timestep ts) 
{

}
void SandboxAppLayer::Detach() 
{
    ENGINE_INFO("Sandbox Layer: ", "Detach");
}
}