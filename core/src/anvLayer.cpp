#include "anvLayer.hpp"

namespace Anvil
{
    AnvilLayer::AnvilLayer(const std::string name) : layer_name{name} { ENGINE_INFO("Layer Created: " + layer_name, "`AnvilLayer()`"); }

    void AnvilLayer::Attach(){};
    void AnvilLayer::Update(Timestep ts){};
    void AnvilLayer::Detach(){};
}

