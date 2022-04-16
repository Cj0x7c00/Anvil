#include "app.hpp"
//#include "window_manager.hpp"    

int main(){    
    try {
        AnvilEngine::AnvilEngineApplication app;
        app.Run();
        
    } 
    catch (std::exception &e){
        std::cout << e.what();
    }
}