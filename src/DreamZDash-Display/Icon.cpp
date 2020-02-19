/*
 * Tristan Hilbert
 * 2/17/2020
 * Icon Source File
 * Definitions for an arbituary icon in the Dashboard
 */

#include "Icon.hpp"
#include "Constants.hpp"

namespace dzdash{

    Icon::Icon(const sf::Vector2f& dim):
        iconTarget(sf::Vector2f(dim.x, dim.y)),
        image(), // Copy Texture
        defaultDimensions(dim),
        costume(0),
        // Empty Function
        task()
    {
        // Implicit Casts
        int width = dim.x;
        int height = dim.y;

        this->iconTarget.setTextureRect(sf::IntRect(0,0,width,height));
    }

    Icon::Icon(
        const std::function<void(void)>& task,
        const sf::Vector2f& dim
    ):
        iconTarget(sf::Vector2f(dim.x, dim.y)),
        image(), // Copy Texture
        defaultDimensions(dim),
        costume(0),
        task(task)
    {
        // Implicit Casts
        int width = dim.x;
        int height = dim.y;

        this->iconTarget.setTextureRect(sf::IntRect(0,0,width,height));
    }

    Icon::~Icon(){   }

    void Icon::draw(sf::RenderWindow& target){
        target.draw(this->iconTarget);
    }

    void Icon::onResize(const sf::Vector2f& size){
        // Think Ratios
        // defaultDimensions.x / defaultRatio.x = icon_size.x / size.x
        // So defaultDimensions * size.x / defaultRatio.x = icon_size.x
        float x = (this->defaultDimensions.x * size.x) / defaultRatio.x;
        float y = (this->defaultDimensions.y * size.y) / defaultRatio.y;
        this->iconTarget.setScale(x,y);

        // Same thing with setPosition
        sf::Vector2f pos = this->iconTarget.getPosition();
        pos.x = (pos.x * size.x) / defaultRatio.x;
        pos.y = (pos.y * size.y) / defaultRatio.y;
        this->iconTarget.setPosition(pos);

    }

    // Animation?
    void Icon::tick(sf::Uint8){ }

    // Fascades for sf::RectangleShape functions
    void Icon::setPosition(const sf::Vector2f& pos){
        this->iconTarget.setPosition(pos);
    }

    sf::Vector2f Icon::getPosition(){
        return this->iconTarget.getPosition();
    }

    void Icon::copySetText(const sf::Texture& text){
        this->image = text;
        this->iconTarget.setTexture(&this->image);
    }

    void Icon::setCostume(sf::Uint8 index){
        // Implicit Casts
        if (index >= 0){
            int width = this->defaultDimensions.x;
            int height = this->defaultDimensions.y;
            sf::Vector2u imageDim = this->image.getSize();
            if(imageDim.x < width * (index + 1)) {
                this->iconTarget.setTextureRect(sf::IntRect(
                    width * index,
                    0,
                    width,
                    height
                ));
            }
        }
    }

    void Icon::nextCostume(sf::Uint8){
        sf::IntRect rect = this->iconTarget.getTextureRect();
        sf::Vector2u imageDim = this->image.getSize();

        if(imageDim.x < rect.left + 2 * rect.width) {
            this->iconTarget.setTextureRect(sf::IntRect(
                rect.left + rect.width,
                0,
                rect.width,
                rect.height
            ));
        }
    }

    void Icon::execute(){
        this->task();
    }

};
