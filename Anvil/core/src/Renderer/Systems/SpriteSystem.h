#pragma once
#include "Base/Pointer.hpp"
#include "../RenderSystem.h"
#include "../Renderer.h"
#include "../GrComp/GraphicsFactory.h"
#include <vector>
#include <Util/anvLog.hpp>

namespace Anvil
{
    class SpriteSystem :
        public RenderSystem
    {
    public:

        SpriteSystem(Ref<SwapChain> _sc) : RenderSystem(_sc)
        {
            ENGINE_INFO("Creating Render System");
        }
        
        ~SpriteSystem() {}

        void Init() override;
        void NewFrame(NewFrameInfo& frameInfo, Ref<Scene> scene) override;

    private:
        void load_shaders();
        void create_pipeline();
        void render_sprites(NewFrameInfo& frameInfo, Ref<Scene> scene);

    private:
        Ref<Pipeline>            m_Pipeline;
        std::vector<Ref<Shader>> m_Shaders;
    };
}

