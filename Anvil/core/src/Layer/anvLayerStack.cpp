#include "anvLayerStack.hpp"

namespace Anvil
{

    LayerStack::~LayerStack()
    {
        for (AnvilLayer* layer : Layers)
        {
            layer->Detach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(AnvilLayer* layer)
    {
        layer->Attach();
        Layers.emplace(Layers.begin() + insertIndex, layer);
        insertIndex++;
    }

    void LayerStack::PopLayer(AnvilLayer* layer)
    {
        auto it = std::find(Layers.begin(), Layers.begin() + insertIndex, layer);
		if (it != Layers.begin() + insertIndex)
		{
			layer->Detach();
			Layers.erase(it);
			insertIndex--;
		}
    }

    std::vector<AnvilLayer*>& LayerStack::GetLayers() { return Layers; }
}