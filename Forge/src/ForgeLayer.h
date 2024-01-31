#pragma once
#include <glm/glm.hpp>
#include "Anvil.hpp"

class ForgeLayer :
    public Anvil::AnvilLayer
{
public:

    ForgeLayer();

    void Attach() override;
    void Update() override;
    void Detach() override;

private:
    SCENE m_Scene;
};

