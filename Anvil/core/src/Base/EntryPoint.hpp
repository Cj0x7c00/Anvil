#pragma once
#include "anvApplication.hpp"   

extern Anvil::AnvilApplication* Anvil::CreateApplication();

int main(){    
    Anvil::ENGINE_INFO("Starting");
    auto app = Anvil::CreateApplication();
    app->Run();
}
