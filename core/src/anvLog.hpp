#pragma once

#include <iostream>
#include <string>
#include "settings.hpp"

class logger{

    public:
        /* 
        LOG  instructions: ("str of what you want to say", <logging code>) 

        logging codes:
            0-info 
            1-debug
            2-warning
            3-error 
        */
        void LOG(std::string log_msg, int log_code){

            if (log_code == 0){ // 0 is code for info
                std::cout << "\033[1;30m[INFO]: \033[0m" << log_msg << '\n';
            }

            if (log_code == 1){ // 1 is code for debug
                std::cout << "\033[1;32m[DEBUG]: \033[0m" << log_msg << '\n';
            }

            if (log_code == 2){ // 2 is code for warning
                std::cout << "\033[1;33m[WARNING]: \033[0m" << log_msg << '\n';
            }

            if (log_code == 3){ //error
                std::cout <<"\033[1;31m[ERROR]: \033[0m";
                throw std::runtime_error(log_msg);
            }

        }

};

logger LOGGER; // logger object

#if defined(DEBUG)
#define ENGINE_INFO(...)  LOGGER.LOG(__VA_ARGS__, 0)
#define ENGINE_DEBUG(...) LOGGER.LOG(__VA_ARGS__, 1)
#define ENGINE_WARN(...)  LOGGER.LOG(__VA_ARGS__, 2)
#define ENGINE_ERROR(...) LOGGER.LOG(__VA_ARGS__, 3)



#elif defined(NDEBUG) // ill fix this later...
#define ENGINE_INFO(...)  0
#define ENGINE_DEBUG(...) 0
#define ENGINE_WARN(...)  0

#endif