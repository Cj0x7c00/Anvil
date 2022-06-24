#pragma once
#include "anvLayer.hpp"

namespace AnvilEngine
{

class basic_anvApp : public AnvilLayer
{
    public:
     std::string name = "basic app";
     int counter = 0;

     basic_anvApp();
     ~basic_anvApp() = default;
     
     void Attach() override;
     void Update() override;
     void Detach() override;
};

}