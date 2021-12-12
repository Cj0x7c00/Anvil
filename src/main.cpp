#include "main.hpp"
#include <iostream>
#include "simple_logger.hpp"


SimpleEngine::App app;    

int main(void){

    try {

        LOGGER.LOG("Running App", 0);
        app.Start();
        LOGGER.LOG("Shutting Down App", 0);
        app.ShutDown();
    } 
    catch (std::exception &e){
        LOGGER.LOG("Failed to run app!", 0);
        std::cout << e.what();
    }
}