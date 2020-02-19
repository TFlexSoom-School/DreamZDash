#pragma once

/*
 * Tristan Hilbert
 * 2/4/2020
 * Constants For DreamZDash Display
 *
 */

#ifndef DREAMZDASH_CONSTANTS_HPP
#define DREAMZDASH_CONSTANTS_HPP
#include <SFML/Graphics.hpp>
#include <string>

namespace dzdash{
    const sf::Vector2u defaultRatio(1333, 750);
    const std::string defaultFontPath =
        "/usr/share/fonts/truetype/liberation/LiberationSerif-Bold.ttf";

    enum INPUT_FLAG : unsigned int{
        INPUT_NONE = 0,
        INPUT_UP,
        INPUT_RIGHT,
        INPUT_DOWN,
        INPUT_LEFT,
        INPUT_SELECT,
        // Add Other Inputs Here
        SOMETHING
    };

};

#endif
