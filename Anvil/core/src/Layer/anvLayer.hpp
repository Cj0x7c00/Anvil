#pragma once
#include <string>
#include "../Util/anvLog.hpp"
#include "../Util/Time/anvTimeStep.hpp"

namespace Anvil{

    class AnvilLayer
    {
        public:
        AnvilLayer(const std::string name = "new layer");
        ~AnvilLayer();

        virtual void Attach(); // Called when loaded
        virtual void Update(Timestep ts); // Called once per frame
        virtual void Detach(); // Called before destructor

        std::string GetName(){ return layer_name; }

        protected:
        const std::string layer_name;
    };
}