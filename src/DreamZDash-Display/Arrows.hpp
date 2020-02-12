#pragma once


#ifndef  DREAMZDASH_ARROWS_HPP
#define DREAMZDASH_ARROWS_HPP

#include <SFML/Graphics.hpp>

namespace dzdash{
class Arrows{
private:
    sf::RectangleShape arrowLeft;
    sf::RectangleShape arrowRight;
    float screenWidth;
    float jiggleFactor;
    void setup();
    void highlight(bool, bool);
    void jiggle(bool, bool);

public:
    Arrows();
    virtual ~Arrows();
    virtual void draw(sf::RenderWindow&);
    virtual void onResize(const sf::Vector2f&);
    virtual void tick(sf::Uint8, bool, bool);

    // Use to do math on where the index of the games
    // is and whether either arrow should be highlighted
    virtual void tick(sf::Uint8, sf::Uint8, sf::Uint8);

};

};


#endif /* end of include guard: DREAMZDASH_ARROWS_HPP */
