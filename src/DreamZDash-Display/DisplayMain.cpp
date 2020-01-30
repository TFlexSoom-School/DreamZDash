/*
 * Tristan Hilbert
 * 1/30/2020
 * Display Main Source File
 * 
 * 
 */

#include "ViewOrchestration.hpp"

int main(int argc, char * argv[]){
    dzdash::ViewOrchestration orch;
    while(orch.isOpen()){
        orch.display();
    }
}