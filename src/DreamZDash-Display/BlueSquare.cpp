/*
 * Tristan Hilbert
 * 2/18/2020
 * Blue Square Source File
 *    GET READY TO START FLYIN!
 *
 */


#include "BlueSquare.hpp"
#include "Constants.hpp"
#include <cmath>

namespace dzdash{
    const double uniformMoveConstant = 20.0;
    const float ratiox = 20.0f;
    const float ratioy = 10.0f;

    sf::Vector2f BlueSquare::getDisplacement(){
        const sf::Vector2f pos = this->square.getPosition();
        float dx = this->destination.x - pos.x;
        float dy = this->destination.y - pos.y;
        double hyp = sqrt(dx * ((double) dx) + dy * ((double) dy));
        if(hyp > uniformMoveConstant){
            dx = (dx * uniformMoveConstant) / hyp;
            dy = (dy * uniformMoveConstant) / hyp;
        }
        return sf::Vector2f(pos.x + dx, pos.y + dy);
    }

    BlueSquare::BlueSquare():
        square(sf::Vector2f(defaultRatio.x / ratiox, defaultRatio.y / ratioy)),
        destination(sf::Vector2f(0.0f,0.0f))
    {
        this->square.setPosition(sf::Vector2f(0.0f,0.0f));
        this->square.setFillColor(sf::Color::Cyan);
    }

    BlueSquare::BlueSquare(const sf::Vector2f& pos):
        square(sf::Vector2f(defaultRatio.x / ratiox, defaultRatio.y / ratioy)),
        destination(pos)
    {
        this->square.setPosition(pos);
        this->square.setFillColor(sf::Color::Cyan);
    }

    BlueSquare::~BlueSquare(){ }

    void BlueSquare::setDestination(const sf::Vector2f& dest){
        this->destination = dest;
    }

    void BlueSquare::setPosition(const sf::Vector2f& pos){
        this->square.setPosition(pos);
    }

    void BlueSquare::setPosAndDest(const sf::Vector2f& pos){
        this->square.setPosition(pos);
        this->destination = pos;
    }

    // Drawings FUNCTIONS
    void BlueSquare::draw(sf::RenderWindow& target){
        target.draw(this->square);
    }

    void BlueSquare::tick(sf::Uint8 frameMod){
        if(this->square.getPosition() != this->destination){
            this->setPosition(this->getDisplacement());
        }
    }

    void BlueSquare::onResize(const sf::Vector2f& size){
        this->square.setSize(sf::Vector2f(size.x / ratiox, size.y / ratioy));

        // Change destination based on difference of present size and past size.
        //this->destination
    }
};
