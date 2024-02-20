#pragma once
#include <glm/glm.hpp>
#include "Anvil.hpp"
#include "pannels/SceneView.h"

class ForgeLayer :
    public Anvil::AnvilLayer
{
public:

    ForgeLayer(SceneManager& manager, Ref<Canvas> canvas);

    void Attach() override;
    void Update() override;
    void Detach() override;

private:
    SceneManager& scManager;
    SceneView* SceneViewPannel;
    Ref<Canvas> m_Canvas;
};

