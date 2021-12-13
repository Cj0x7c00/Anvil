#pragma once

#include <iostream>
#include <string>

class logger{

    public:

        /* LOG instructions: ("str of what you want to say", <loggin code>) 

        logging codes:
            0-info 
            1-debug
            2-error, will stop the program 
        */
        void LOG(std::string log_msg, int log_code){

            if (log_code == 0){ // 0 is code for info
                std::cout << "\033[1;31m[INFO]: \033[0m" << log_msg << '\n';
            }

            if (log_code == 1){ // 1 is code for debug
                std::cout << "\033[1;31m[DEBUG]: \033[0m" << log_msg << '\n';
            }

            if (log_code == 2){ // 2 is code for error
                std::cout << "\033[1;31m[ERROR]: \033[0m";
                throw std::runtime_error(log_msg);
            }

        }

};

logger LOGGER; //logger object
