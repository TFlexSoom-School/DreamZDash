/*
 * Tristan Hilbert
 * 1/30/2020
 * View Orchestration Source File
 *
 */

#include "ViewOrchestration.hpp"
#include "Constants.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace dzdash{

ViewOrchestration::ViewOrchestration():
    window(),
    back()
{

    /*std::function<void()> resizeHook(
        [&](){
            sf::Vector2f size = this->window.getSize();
            this->back.onResize(size);
        }
    );

    this->window.setOnResize(resizeHook);*/
}

ViewOrchestration::~ViewOrchestration(){
    this->window.close();
}

void ViewOrchestration::display(){
    this->back.draw(this->window);
    this->window.display();
}

bool ViewOrchestration::isOpen(){
    return this->window.isOpen();
}

};
