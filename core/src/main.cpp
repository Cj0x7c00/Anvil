#include "main.hpp"
//#include "window_manager.hpp"    

AnvilEngine::AnvilEngineApplication app;

int main(){    
    try {
        app.Run();
        
    } 
    catch (std::exception &e){
        std::cout << e.what();
    }
}
