/*
 * Tristan Hilbert
 * 2/5/2020
 * Example of Running Commands on Commandline
 */


#include <cstdlib>
#include <iostream>

void open_app(){
    system("chromium http://localhost/game");
}

int main(){
    std::cout << "Hello There this is a C++ application" << std::endl;
    open_app();
    std::cout << "End" << std::endl;
    return 0;
}
