#pragma once
#include <glm/glm.hpp>
#include <Anvil.hpp>

using namespace Anvil;


class ForgeLayer :
    public Anvil::AnvilLayer
{
public:

    ForgeLayer(SceneManager& manager);

    static void CreateSprite();

    void Attach() override;
    void Update() override;
    void OnGUI()  override;
    void Detach() override;



private:
    SceneManager& scManager;
    static SCENE activeScene;

    Anvil::Ref<Anvil::Canvas> canvas;
    Anvil::Ref<UI_TEXT> pos;
    Anvil::Ref<UI_TEXT> rot;

    Anvil::Camera& camera;
    Anvil::CameraController cController;

    static ENTITY Quad1;
    static ENTITY Quad2;

};

