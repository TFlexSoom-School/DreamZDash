/*
 * Tristan Hilbert
 * 2/4/2020
 * Background Sprite Source file
 *
 */

#include "Background.hpp"
#include "Constants.hpp"

namespace dzdash{
//    std::vector<sf::Drawable> draws;

void Background::setup(){
    // Get Vector ready for rectangles
    this->draws.resize(3);

    // Temp rectangle
    sf::RectangleShape rect(sf::Vector2f(defaultRatio.x, defaultRatio.y));

    // Ready first black rectangle for backdrop of background
    rect.setFillColor(sf::Color::Black);

    // Submit copy to vector
    this->draws.push_back(rect);

    // Ready color for other two rectangles
    rect.setFillColor(sf::Color::White);

    // Thin Rectangle
    rect.setSize(sf::Vector2f(defaultRatio.x, defaultRatio.y / 6));

    // Submit copy of top white border rectangle
    this->draws.push_back(rect);

    // Offset bottom Rectangle
    rect.setPosition(0.0, (float) defaultRatio.y - defaultRatio.y / 6);

    // Submit copy of bottom white border rectangle
    this->draws.push_back(rect);

}

Background::Background():
    draws()
{
    this->setup();
}

Background::~Background(){
    this->draws.clear();
}

void Background::draw(sf::RenderWindow& target){

    for(int i = 0; i < this->draws.size(); i ++){
        // Second Parameter can use RenderStates
        target.draw(this->draws[i]);
    }
}


void Background::resize(const sf::Vector2f& size){
    // Since implementation knows what the contents of draws
    // is, we should cast as necessary for resizing

    sf::RectangleShape* rect = &this->draws[0];
    // Resize first to full screen
    rect->setSize(size);

    // Resize Second Rectangle
    rect = &this->draws[1];
    const sf::Vector2f newThinSize(size.x, size.y / 6.0);
    rect->setSize(newThinSize); // Second arg casts to int

    // Resize and Re-offset third rectangle.
    rect = &this->draws[2];
    rect->setSize(newThinSize);
    rect->setPosition(0.0, (float) defaultRatio.y - defaultRatio.y / 6);
}


};
