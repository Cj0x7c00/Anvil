#include "main.hpp"
#include "window_manager.hpp"

AnvilEngine::AnvilEngineApplication app;    

int main(){

    ENGINE_INFO("Attempting to start engine");    
    try {
        ENGINE_INFO("Starting Engine");
        ENGINE_INFO(glfwGetVersionString());
        app.Start();
        ENGINE_INFO("Stopping Engine");
        app.ShutDown();
        
    } 
    catch (std::exception &e){
        std::cout << e.what();
    }
}