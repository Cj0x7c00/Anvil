#pragma once
#include <string>
#include "../Util/anvLog.hpp"
#include "../Util/Time/anvTimeStep.hpp"

namespace Anvil{

    class AnvilLayer
    {
    
    public:
        AnvilLayer(const std::string name = "new layer");

        // Called when loaded
        virtual void Attach() = 0; 
        // Called once per frame
        virtual void Update() = 0; 
        // Called before destructor
        virtual void Detach() = 0; 

        std::string GetName(){ return layer_name; }

    protected:
        const std::string layer_name;
    
    };
}