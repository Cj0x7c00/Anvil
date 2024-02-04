#pragma once
#include "Base/Pointer.hpp"
#include "../UBO.h"
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
        
        ~SpriteSystem();

        void Init() override;
        void Update(NewFrameInfo& frameInfo) override;
        void NewFrame(NewFrameInfo& frameInfo) override;
        void create_ubos() override;
        void update_ubos(NewFrameInfo& frameInfo) override;
        void create_descriptor_pool() override;
        void create_descriptor_sets() override;

    private:
        void load_shaders();
        void create_pipeline();
        void render_sprites(NewFrameInfo& frameInfo);

    private:
        UniformBufferObject      m_Ubo{};
        std::once_flag           m_InitFlag;
        Ref<Pipeline>            m_Pipeline;
        std::vector<Ref<Shader>> m_Shaders;
    };
}

