#pragma once

/*
 * Tristan Hilbert
 * 1/30/2020
 * Graphical Display Object
 * 
 * This object will work as the engine pushing the actual graphical implementations
 * loaded as a part of DreamZDash-Display.
 * 
 */

#ifndef DREAMZDASH_VIEW_ORCHESTRATION
#define DREAMZDASH_VIEW_ORCHESTRATION

#include <SFML/Graphics.hpp>

namespace dzdash{

class ViewOrchestration{
    private:
    sf::RenderWindow window;

    public:
    ViewOrchestration();
    virtual ~ViewOrchestration();
    virtual void display();

    virtual bool isOpen();

};

};

#endif