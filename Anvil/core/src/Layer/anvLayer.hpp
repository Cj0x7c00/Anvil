#pragma once
#include <string>
#include "../input/Event.h"
#include "../Base/macros.hpp"
#include "../Util/anvLog.hpp"

namespace Anvil{

    class ANV_API AnvilLayer
    {
    
    public:
        AnvilLayer(const std::string name = "new layer");

        // Called when loaded
        virtual void Attach() = 0; 
        // Called once per frame
        virtual void Update() = 0; 
        // Called for UI Rendering
        virtual void OnGUI() = 0;
        // Called when input happens
        //virtual void OnInput(Event& event) = 0;
        // Called before destructor
        virtual void Detach() = 0; 

        std::string GetName(){ return layer_name; }

    protected:
        const std::string layer_name;
    
    };
}