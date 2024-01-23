#pragma once
#include "../RenderSystem.h"

#include "Base/Pointer.hpp"
#include "../GrComp/GraphicsFactory.h"

#include <vector>

namespace Anvil
{
    class defaultRS :
        public RenderSystem
    {
    public:
        void Init() override;
        void NewFrame() override;

    private:
        void load_shaders();
        void create_pipeline();

    private:
        Ref<Pipeline>            m_Pipeline;
        std::vector<Ref<Shader>> m_Shaders;
    };
}

