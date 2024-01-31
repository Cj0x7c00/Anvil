#pragma once
#include "Base/Pointer.hpp"
#include "../RenderSystem.h"
#include "../Renderer.h"
#include "../GrComp/GraphicsFactory.h"

#include <vector>
#include <Util/anvLog.hpp>

namespace Anvil
{
    class SceneSys :
        public RenderSystem
    {
    public:

        SceneSys(Ref<SwapChain> _sc) : RenderSystem(_sc)
        {
            ENGINE_INFO("Creating Render System");
        }
        
        ~SceneSys() {}

        void Init() override;
        void NewFrame(NewFrameInfo& frameInfo, Ref<Scene> scene) override;
        void NewFrame(NewFrameInfo& frameInfo) override {};

    private:
        void load_shaders();
        void create_pipeline();

    private:
        Ref<Pipeline>            m_Pipeline;
        std::vector<Ref<Shader>> m_Shaders;
    };
}

