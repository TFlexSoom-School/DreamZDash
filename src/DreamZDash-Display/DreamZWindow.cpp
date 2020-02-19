/*
 * Tristan Hilbert
 * 2/4/2020
 * DreamZWindow Source file
 *
 */

#include <utility>
#include "DreamZWindow.hpp"
#include "Constants.hpp"

//    std::function<void, void> lambdaCreate;
//    std::function<void, void> lambdaResize;

namespace dzdash{

Window::Window():
    sf::RenderWindow(
        sf::VideoMode(defaultRatio.x, defaultRatio.y),
        "Default Dashboard"
    ),
    // Both functions should be void-full lambda functions
    // These functions should do nothing
    // They are the equivalent of setting null while still be callable
    lambdaCreate([](){}),
    lambdaResize([](){})
{ }

Window::Window(
    sf::VideoMode mode,
    const sf::String& title,
    sf::Uint32 style,
    const sf::ContextSettings& settings
):
    sf::RenderWindow(mode, title, style, settings),
    // Both functions should be void-full lambda functions
    // These functions should do nothing
    // They are the equivalent of setting null while still be callable
    lambdaCreate([](){}),
    lambdaResize([](){})
{ }

Window::~Window(){

}

void Window::setOnCreate(const std::function<void()>& func){
    this->lambdaCreate = std::move(func);
}

void Window::setOnResize(const std::function<void()>& func){
    this->lambdaResize = std::move(func);
}


// TODO Penetration Test
/*
 * Observation
 * Calling just any code is problematic. Perhaps a structure for these function
 * variables (closures if you will) should be a struct with hashes. The hashes
 * should match up to computed hashes within the constants set. This way only
 * our created functions are called. Food for thought.
 */

void Window::onCreate(){
    this->lambdaCreate();
}

void Window::onResize(){
    this->lambdaResize();
}

};
