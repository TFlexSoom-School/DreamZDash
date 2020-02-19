#pragma once

/*
 * Tristan Hilbert
 * 2/17/2020
 * Icon Sprite Header File
 * These Icons are selectable and live around the Dashboard
 */


#ifndef DREAMZDASH_ICON_HPP
#define DREAMZDASH_ICON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

namespace dzdash{
class Icon{
    private:
    // Provides where the icon will render and what part
    // of the texture it will render
    sf::RectangleShape iconTarget;

    // Provides the image the icon will render from
    sf::Texture image;

    // Provides the dimensions based on 800x600 window
    sf::Vector2f defaultDimensions;

    // Provides Index of which section of image the icon
    // Should be at with iconTarget
    // Defaulted at 0
    sf::Uint8 costume;

    // A Function to call when "launched" or "selected"
    std::function<void(void)> task;

public:
    // Texture should be copied!!!
    Icon(
        const sf::Vector2f& dim = sf::Vector2f(25, 25)
    );

    // Texture should be copied!!!
    Icon(
        const std::function<void(void)>&,
        const sf::Vector2f& dim = sf::Vector2f(25, 25)
    );

    virtual ~Icon();

    virtual void draw(sf::RenderWindow&);
    virtual void onResize(const sf::Vector2f&);
    virtual void tick(sf::Uint8);

    // Fascades for sf::RectangleShape functions
    virtual void setPosition(const sf::Vector2f&);
    virtual sf::Vector2f getPosition();

    // Function to set Texture
    /*
     * It is possible to do this at construction, but then functionality
     * must be added to correctly copy the fields of the object. Otherwise
     * no texture will be shown.
     */
    virtual void copySetText(const sf::Texture&);

    virtual void setCostume(sf::Uint8 index = 0);
    virtual void nextCostume(sf::Uint8);

    virtual void execute();
};
};



#endif /* end of include guard: DREAMZDASH_ICON_HPP */
