#pragma once
#include "settings.hpp"
#include <iostream>
#include <string>


class logger{

    public:
        /* 
        LOG  instructions: ("str of what you want to say", "location", <logging code>) 

        logging codes:
            0-info 
            1-debug
            2-warning
            3-error 
        */

       // TODO: Add Special Info log
        static void LOG(std::string log_msg, std::string log_location, int log_code){

            if (log_code == 0){ // 0 is code for info
                std::cout << "\033[1;30m[INFO] \033[0m" << "\033[1;30m[" << "Location: " << log_location << "]: \033[0m"<< log_msg << '\n';
            }

            if (log_code == 1){ // 1 is code for debug
                std::cout << "\033[1;32m[DEBUG] \033[0m" << "\033[1;30m[" << "Location: " << log_location << "]: \033[0m" << log_msg << '\n';
            }

            if (log_code == 2){ // 2 is code for warning
                std::cout << "\033[1;33m[WARNING] \033[0m" << "\033[1;30m[" << "Location: " << log_location << "]: \033[0m" << log_msg << '\n';
            }

            if (log_code == 3){ //error
                std::cout <<"\033[1;31m[ERROR] \033[0m" << "\033[1;30m[" << "Location: " << log_location << "]: \033[0m\n";
                throw std::runtime_error(log_msg);
            }

        }

};


#if defined(DEBUG)
#define ENGINE_INFO(...)  logger::LOG(__VA_ARGS__, 0)
#define ENGINE_DEBUG(...) logger::LOG(__VA_ARGS__, 1)
#define ENGINE_WARN(...)  logger::LOG(__VA_ARGS__, 2)
#define ENGINE_ERROR(...) logger::LOG(__VA_ARGS__, 3)

#define ENGINE_ASSERT(e) (__builtin_expect(!(e), 0) ? __assert_rtn(__func__, __FILE__, __LINE__, #e) : (void)0)


//#elif defined(NDEBUG) // ill fix this later...
//#define ENGINE_INFO(...)  0
//#define ENGINE_DEBUG(...) 0
//#define ENGINE_WARN(...)  0

#endif