#pragma once


#ifndef  DREAMZDASH_ARROWS_HPP
#define DREAMZDASH_ARROWS_HPP

#include <SFML/Graphics.hpp>

namespace dzdash{
class Arrows{
private:
    sf::RectangleShape arrowLeft;
    sf::RectangleShape arrowRight;
    void setup();
    void highlight(bool, bool);

public:
    Arrows();
    virtual ~Arrows();
    virtual void draw();
    virtual void tick(bool, bool);
    virtual void tick(Uint8, Uint8);

};

};


#endif /* end of include guard: DREAMZDASH_ARROWS_HPP */
