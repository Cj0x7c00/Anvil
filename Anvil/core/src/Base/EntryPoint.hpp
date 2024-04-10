#pragma once
#include "anvApplication.hpp"   

extern Anvil::AnvilApplication* Anvil::CreateApplication();

#ifdef DEBUG
    int main(){    
        Anvil::ANVIL_OUT("Starting");
        
        auto app = Anvil::CreateApplication();
        try {
            app->Run();
        }
        catch (std::exception& e)
        {
            ANVIL_ERROR("Failed to launch: {}", e.what());
        }

        delete app;
    }
#endif

#ifdef RELEASE
int WinMain()
{
    Anvil::ANVIL_OUT("Starting");

    auto app = Anvil::CreateApplication();
    try {
        app->Run();
    }
    catch (std::exception& e)
    {
        ANVIL_ERROR("Failed to launch: {}", e.what());
    }

    delete app;
}
#endif // RELEASE
