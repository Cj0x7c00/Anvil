#pragma once
#include "anvApplication.hpp"   

extern Anvil::AnvilApplication* Anvil::CreateApplication();

int main(){    
    Anvil::ANVIL_OUT("Starting");
    auto app = Anvil::CreateApplication();
    app->Run();
    delete app;
}
