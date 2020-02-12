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
    sf::Event event;
    while(orch.window.isOpen()){
        if(orch.window.pollEvent(event)){
            // Close window: exit
            if (event.type == sf::Event::Closed)
                orch.window.close();
        }

        orch.displayToWindow();

        orch.tick();
    }
}
