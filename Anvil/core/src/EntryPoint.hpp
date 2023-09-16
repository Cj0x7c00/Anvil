#pragma once
#include "anvApplication.hpp"   

extern Anvil::AnvilApplication* Anvil::CreateApplication();

int main(){    
    try {
        auto app = Anvil::CreateApplication();
        app->Run();
    } 
    catch (std::exception &e){
        ENGINE_ERROR(e.what());
    }
}