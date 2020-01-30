/*
 * Tristan Hilbert
 * 1/30/2020
 * View Orchestration Source File
 * 
 */

#include "ViewOrchestration.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

namespace dzdash{

ViewOrchestration::ViewOrchestration(): 
    window(sf::VideoMode(800,600), "DZDash-Window")
{
    std::cout << "View Created" << std::endl;
}

ViewOrchestration::~ViewOrchestration(){
    this->window.close();
}

void ViewOrchestration::display(){
    sf::RectangleShape rect(sf::Vector2f(200,200));
    rect.setFillColor(sf::Color(255, 255, 255));
    
    this->window.clear();
    this->window.draw(rect);
    this->window.display();

}

bool ViewOrchestration::isOpen(){
    return this->window.isOpen();
}

};