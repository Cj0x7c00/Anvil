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
    class UISystem :
        public RenderSystem
    {
    public:

        UISystem(Ref<SwapChain> _sc) : RenderSystem(_sc)
        {
            ENGINE_INFO("Creating UI System");
        }

        ~UISystem();

        void Init() override;
        void OnCallOnce(CommandBuffer cmdBuffer) override;
        void NewFrame(NewFrameInfo& frameInfo) override;

        void create_descriptor_pool() override;
        //void create_descriptor_sets() override;

    private:
        void load_anvil_colors();
    private:
        UniformBufferObject      m_Ubo{};
        Ref<Pipeline>            m_Pipeline;
        std::vector<Ref<Shader>> m_Shaders;
    };
}

