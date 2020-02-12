/*
 * Tristan Hilbert
 * 1/30/2020
 * View Orchestration Source File
 *
 */

#include "ViewOrchestration.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>

namespace dzdash{

ViewOrchestration::ViewOrchestration():
    window(),
    back(),
    arrows(),
    frameMod(0)
{

    /*std::function<void()> resizeHook(
        [&](){
            sf::Vector2f size = this->window.getSize();
            this->back.onResize(size);
            this->arrows.onResize(size);
        }
    );

    this->window.setOnResize(resizeHook);*/
}

ViewOrchestration::~ViewOrchestration(){
    this->window.close();
}

void ViewOrchestration::displayToWindow(){
    this->window.clear();
    this->back.draw(this->window);
    this->arrows.draw(this->window);
    this->window.display();
}

void ViewOrchestration::tick(){
    this->frameMod = (this->frameMod + 1) % 60;
    this->arrows.tick(this->frameMod, true, true);
}

};
