#pragma once
#include <string>
#include "anvLog.hpp"

namespace AnvilEngine{

    class AnvilLayer
    {
        public:
        AnvilLayer(const std::string name = "new layer");

        virtual void Attach();
        virtual void Update();
        virtual void Detach();

        std::string GetName(){ return layer_name; }

        protected:
        const std::string layer_name;
    };
}