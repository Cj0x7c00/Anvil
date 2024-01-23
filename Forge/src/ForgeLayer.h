#pragma once
#include "Anvil.hpp"
#include "Rendering.hpp"

class ForgeLayer :
    public Anvil::AnvilLayer
{
public:

    ForgeLayer();

    void Attach() override;
    void Update() override;
    void Detach() override;

};

