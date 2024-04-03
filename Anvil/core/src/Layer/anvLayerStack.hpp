#pragma once
#include "anvLayer.hpp"
#include <vector>

namespace Anvil
{

    class ANV_API LayerStack
    {

    public:

        ~LayerStack();

        void PushLayer(AnvilLayer* layer);
        void PopLayer(AnvilLayer* layer);

        static std::vector<AnvilLayer*>& GetLayers();

    private:
        unsigned int insertIndex = 0;
        static std::vector<AnvilLayer*> Layers;
    };
}