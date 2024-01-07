#pragma once
#include "anvLayer.hpp"
#include <vector>

namespace Anvil
{

    class LayerStack
    {
    private:
        static LayerStack* instance;

    public:
        static LayerStack* Instance()
        {
            if (instance == nullptr)
            {
                instance = new LayerStack();
            }
            return instance;
        }

        void PushLayer(AnvilLayer* layer);
        void PopLayer(AnvilLayer* layer);

        std::vector<AnvilLayer*>& GetLayers();

    private:
        LayerStack();
        ~LayerStack();
        LayerStack(const LayerStack&) = delete;
        LayerStack& operator=(const LayerStack&) = delete;

        unsigned int insertIndex = 0;
        std::vector<AnvilLayer*> Layers;
    };
}