#pragma once
#include "../RenderSystem.h"
#include "Base/Pointer.hpp"
#include "../GrComp/GraphicsFactory.h"
#include <vector>
#include <Util/anvLog.hpp>

namespace Anvil
{
    class defaultRS :
        public RenderSystem
    {
    public:

        defaultRS(Ref<SwapChain> _sc) : RenderSystem(_sc)
        {
            ENGINE_INFO("Creating Render System");
        }
        
        ~defaultRS() {}

        void Init() override;
        void NewFrame(Ref<RenderPass> renderPass, Ref<Scene> scene) override {};
        void NewFrame(Ref<RenderPass> renderPass, uint32_t imageIndex) override;

    private:
        void load_shaders();
        void create_pipeline();

    private:
        Ref<Pipeline>            m_Pipeline;
        std::vector<Ref<Shader>> m_Shaders;
    };
}

