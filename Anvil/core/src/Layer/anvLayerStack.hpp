#pragma once
#include "anvLayer.hpp"
#include <vector>

namespace Anvil
{
    class AnvilLayerStack
    {
        public:
         std::vector<AnvilLayer*> Layers;
         unsigned int insertIndex;
         
         AnvilLayerStack(){};
         ~AnvilLayerStack();
         void PushLayer(AnvilLayer* layer);
         void PopLayer(AnvilLayer* layer);
    };
}