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

#ifndef DREAMZDASH_VIEW_ORCHESTRATION
#define DREAMZDASH_VIEW_ORCHESTRATION

#include "DreamZWindow.hpp"
#include "Background.hpp"

namespace dzdash{


class ViewOrchestration{
    private:
    // See DreamZWindow.hpp
    Window window;
    Background back;

    public:
    ViewOrchestration();
    virtual ~ViewOrchestration();
    virtual void display();

    virtual bool isOpen();

};

};

#endif
