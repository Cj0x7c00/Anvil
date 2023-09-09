#include "anvLayerStack.hpp"

namespace Anvil
{
    AnvilLayerStack::~AnvilLayerStack()
    {
        for (AnvilLayer* layer : Layers)
        {
            layer->Detach();
            delete layer;
        }
    }

    void AnvilLayerStack::PushLayer(AnvilLayer* layer)
    {
        Layers.emplace(Layers.begin() + insertIndex, layer);
        insertIndex++;
    }

    void AnvilLayerStack::PopLayer(AnvilLayer* layer)
    {
        auto it = std::find(Layers.begin(), Layers.begin() + insertIndex, layer);
		if (it != Layers.begin() + insertIndex)
		{
			layer->Detach();
			Layers.erase(it);
			insertIndex--;
		}
    }
}