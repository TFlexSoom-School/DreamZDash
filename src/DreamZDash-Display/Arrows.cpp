/*
 * Tristan Hilbert
 * 2/7/2020
 * Dashboard Game Preview Arrows Source File
 *
 */

/*
sf::RectangleShape arrowLeft;
sf::RectangleShape arrowRight;
*/

#include "Arrows.hpp"
#include "Constants.hpp"
#include <iostream>

namespace dzdash{

void Arrows::setup(){
    this->arrowLeft.setPosition(sf::Vector2f(
        0.0f,
        defaultRatio.y / 24.0f * 9.0f
    ));

    this->arrowRight.setPosition(sf::Vector2f(
        this->screenWidth - this->arrowRight.getSize().x,
        defaultRatio.y / 24.0f * 9.0f
    ));

    // default to right arrow having more games at start
    this->highlight(false, true);

    // Set Jiggle Factor to be size.x / 80
    this->jiggleFactor = defaultRatio.x / 80.0f;
}

void Arrows::highlight(bool isLeftHighlight, bool isRightHighlight){
    if(isLeftHighlight){
        this->arrowLeft.setFillColor(sf::Color::White);
    }else{
        this->arrowLeft.setFillColor(sf::Color::Black);
    }

    if(isRightHighlight){
        this->arrowRight.setFillColor(sf::Color::White);
    }else{
        this->arrowRight.setFillColor(sf::Color::Black);
    }
}

void Arrows::jiggle(bool isLeftHighlight, bool isRightHighlight){
    // Jiggle Highlighted Arrow(s)
    if(isLeftHighlight){
        if(this->arrowLeft.getPosition().x < this->jiggleFactor){
            this->arrowLeft.move(1.0f, 0);
        }else{
            this->arrowLeft.setPosition(sf::Vector2f(
                0.0f,
                this->arrowRight.getPosition().y
            ));
        }
    }

    if(isRightHighlight){

        const float jiggleBound = this->screenWidth -
            this->jiggleFactor - this->arrowRight.getSize().x;

        if(this->arrowRight.getPosition().x > jiggleBound){
            this->arrowRight.move(-1.0f, 0);
        }else{
            this->arrowRight.setPosition(sf::Vector2f(
                this->screenWidth - this->arrowRight.getSize().x,
                this->arrowRight.getPosition().y
            ));
        }
    }
}


Arrows::Arrows():
    arrowLeft(sf::Vector2f(defaultRatio.x / 16.0f, defaultRatio.y / 5.0f)),
    arrowRight(sf::Vector2f(defaultRatio.x / 16.0f, defaultRatio.y / 5.0f)),
    screenWidth(defaultRatio.x),
    jiggleFactor(0.0f)
{
    this->setup();
}

Arrows::~Arrows(){ }

void Arrows::draw(sf::RenderWindow& target){
    target.draw(this->arrowLeft);
    target.draw(this->arrowRight);
}

void Arrows::onResize(const sf::Vector2f& size){
    this->screenWidth = size.x;

    this->arrowLeft.setSize(sf::Vector2f(size.x / 16.0f, size.y / 5.0f));
    this->arrowLeft.setPosition(sf::Vector2f(
        0.0f,
        size.y / 12.0f * 5.0f
    ));

    this->arrowRight.setSize(sf::Vector2f(size.x / 16.0f, size.y / 5.0f));
    this->arrowRight.setPosition(sf::Vector2f(
        size.x - this->arrowRight.getSize().x,
        size.y / 12.0f * 5.0f
    ));

    // Set Jiggle Factor to be size.x / 80
    this->jiggleFactor = size.x / 80.0f;

}

void Arrows::tick(sf::Uint8 frameMod, bool isLeftHighlight, bool isRightHighlight){
    this->highlight(isLeftHighlight, isRightHighlight);
    if(frameMod % 5 == 0){
        this->jiggle(isLeftHighlight, isRightHighlight);
    }

}

void Arrows::tick(sf::Uint8 frameMod, sf::Uint8 index, sf::Uint8 size){
    const bool isLeftHighlight = index != 0;
    const bool isRightHighlight = index != size;
    this->highlight(isLeftHighlight, isRightHighlight);

    if(frameMod % 5 == 0){
        this->jiggle(isLeftHighlight, isRightHighlight);
    }
}

};
