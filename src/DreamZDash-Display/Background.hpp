#pragma once
/*
 * Tristan Hilbert
 * 2/4/2020
 * Background Sprite Headerfile
 * This object is to be used in conjunction with View ViewOrchestration
 *
 */

#ifndef DREAMZDASH_BACKGROUND_HPP
#define DREAMZDASH_BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <vector>

namespace dzdash{
class Background{
    private:
    std::vector<sf::RectangleShape> draws;
    void setup();

    public:
        Background();
        virtual ~Background();
        virtual void draw(sf::RenderWindow&);
        virtual void resize(const sf::Vector2f&);


};
};

#endif
