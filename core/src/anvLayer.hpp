#pragma once
#include <string>
#include "anvLog.hpp"
#include "anvTimeStep.hpp"

namespace Anvil{

    class AnvilLayer
    {
        public:
        AnvilLayer(const std::string name = "new layer");

        virtual void Attach(); // Called when loaded
        virtual void Update(Timestep ts); // Called once per frame
        virtual void Detach(); // Called before destructor

        std::string GetName(){ return layer_name; }

        protected:
        const std::string layer_name;
    };
}