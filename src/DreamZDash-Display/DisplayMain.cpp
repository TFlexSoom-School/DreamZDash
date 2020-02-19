/*
 * Tristan Hilbert
 * 1/30/2020
 * Display Main Source File
 *
 *
 */

#include "ViewOrchestration.hpp"
#include "Constants.hpp"
#include <SFML/Window.hpp>

const int input_delay_max = 20;

bool sendInput(dzdash::ViewOrchestration& orch){
    if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)
    ){
        orch.input(dzdash::INPUT_FLAG::INPUT_UP);
        return true;
    }

    if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)
    ){
        orch.input(dzdash::INPUT_FLAG::INPUT_RIGHT);
        return true;
    }

    if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S)
    ){
        orch.input(dzdash::INPUT_FLAG::INPUT_DOWN);
        return true;
    }

    if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)
    ){
        orch.input(dzdash::INPUT_FLAG::INPUT_LEFT);
        return true;
    }

    if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::E) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
    ){
        orch.input(dzdash::INPUT_FLAG::INPUT_SELECT);
        return true;
    }

    return false;
}

int main(int argc, char * argv[]){
    dzdash::ViewOrchestration orch;
    sf::Event event;
    int input_delay = input_delay_max;
    while(orch.window.isOpen()){
        if(orch.window.pollEvent(event)){
            // Close window: exit
            if (event.type == sf::Event::Closed){
                orch.window.close();
            }

        }

        orch.displayToWindow();

        orch.tick();

        if(input_delay == input_delay_max){
            if(sendInput(orch)){
                input_delay = 0;
            }
        }else{
            input_delay ++;
        }
    }
}
