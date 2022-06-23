// Entry Point
#include "app.hpp"   

int main(){    
    try {
        AnvilEngine::AnvilEngineApplication app;
        app.Run();
    } 
    catch (std::exception &e){
        ENGINE_ERROR(e.what(), " ");
    }
}