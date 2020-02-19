
/*
 * Tristan Hilbert
 * 2/19/2020
 * ForeignProcessExchange Source File
 *
 * This should implement Shared Memory through POSIX API
 */

#include "ForeignProcessExchange.hpp"
#include <cstdlib>

namespace dzdash{
    void execute_game(std::string command){
        if(command.size() == 0){
            system("chromium-browser ~/games/index.html");
        }else{
            system(command.c_str());
        }
    }
};
