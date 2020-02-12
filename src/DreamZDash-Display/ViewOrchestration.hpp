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

/*
 * ViewOrchestration Composition
 *
 * Background z-0
 * Dash Arrows z-1
 * Icons z-2
 * GamePreview z-3
 */

#ifndef DREAMZDASH_VIEW_ORCHESTRATION_HPP
#define DREAMZDASH_VIEW_ORCHESTRATION_HPP

#include "DreamZWindow.hpp"
#include "Background.hpp"
#include "Arrows.hpp"

namespace dzdash{


class ViewOrchestration{
    private:
    // See DreamZWindow.hpp
    Background back;
    Arrows arrows;
    sf::Uint8 frameMod;

    public:
    // I want to have access to all window functions!
    Window window;

    public:
    ViewOrchestration();
    virtual ~ViewOrchestration();
    virtual void displayToWindow();
    virtual void tick();


};

};

#endif
