#pragma

/*
 * Tristan Hilbert
 * 2/18/2020
 * Blue Square Header File
 * This represents a square that can "slide to"
 * a given location
 */

#ifndef DREAMZDASH_BLUE_SQUARE_HPP
#define DREAMZDASH_BLUE_SQUARE_HPP

#include <SFML/Graphics.hpp>

namespace dzdash{
class BlueSquare{
    private:
    sf::RectangleShape square;
    sf::Vector2f destination;

    private:
    // Get a new position based on the scaler of the difference between
    // square.position and destination
    sf::Vector2f getDisplacement();

    public:
    BlueSquare();
    BlueSquare(const sf::Vector2f& pos);
    virtual ~BlueSquare();
    virtual void setDestination(const sf::Vector2f&);
    virtual void setPosition(const sf::Vector2f&);
    virtual void setPosAndDest(const sf::Vector2f&);


    // Drawings FUNCTIONS
    virtual void draw(sf::RenderWindow&);
    virtual void tick(sf::Uint8);
    virtual void onResize(const sf::Vector2f&);
};

};



#endif /* end of include guard: DREAMZDASH_BLUE_SQUARE_HPP */
