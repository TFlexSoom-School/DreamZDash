/*
 * Tristan Hilbert
 * 1/30/2020
 * View Orchestration Source File
 *
 */

#include "ViewOrchestration.hpp"
#include <vector>
#include <iostream>

namespace dzdash{
// ------- PRIVATE FUNCTIONS ---------
void ViewOrchestration::setupIcons(){
    // Get space for these sprites
    this->icons.reserve(4);

    // Since the icons will copy the textures
    //    we can allocate them on the stack
    sf::Texture textTemp;

    // Constants to do math off of
    const int iDim = 64;
    const float fDim = iDim;
    const float fDimHalf = fDim / 2.0f;

    // Battery Status Icon
    textTemp.loadFromFile("./assets/full_battery.png");
    /*
     * TODO
     * When we actually load this in, we should add to the texture
     * to create a sprite map for the different batteries.
     * The textTemp object can do that here.
     *
     */
    this->icons.push_back(Icon(sf::Vector2f(iDim, iDim)));
    this->icons[0].setPosition(sf::Vector2f(
        defaultRatio.x * 5.0f / 6.0f,
        defaultRatio.y * 11.0f / 12.0f - fDimHalf
    ));
    this->icons[0].copySetText(textTemp);

    // Settings Icon
    textTemp.loadFromFile("./assets/settings.png");
    this->icons.push_back(Icon(sf::Vector2f(64, 64)));
    this->icons[1].setPosition(sf::Vector2f(
        defaultRatio.x / 12.0f,
        defaultRatio.y / 36.0f
    ));
    this->icons[1].copySetText(textTemp);

    // Wifi icon
    // Might want a better picture
    textTemp.loadFromFile("./assets/external.png");
    this->icons.push_back(Icon(sf::Vector2f(64, 64)));
    this->icons[2].setPosition(sf::Vector2f(
        defaultRatio.x * 5.0f / 6.0f,
        defaultRatio.y / 36.0f
    ));
    this->icons[2].copySetText(textTemp);

    // Power Button Icon
    // Might want a better picture
    textTemp.loadFromFile("./assets/plus.png");
    this->icons.push_back(Icon(sf::Vector2f(64, 64)));
    this->icons[3].setPosition(sf::Vector2f(
        defaultRatio.x / 2.0f - fDimHalf / 2.0f,
        defaultRatio.y * 11.0f / 12.0f - fDimHalf
    ));
    this->icons[3].copySetText(textTemp);
}


// ------- PUBLIC FUNCTIONS ----------

ViewOrchestration::ViewOrchestration():
    window(),
    back(),
    arrows(),
    gamePreview(),
    icons(),
    frameMod(0)
{
    std::vector<GameStruct> list;
    list.reserve(5);

    sf::Texture text;
    text.loadFromFile("./assets/Weeb.png");
    GameStruct temp = {0, text, "Game Name Here", "Developer Here"};

    for(int i = 0; i < 5; i ++){
        list.push_back(temp);
        temp.UID += 1;
        temp.name += "r";
    }

    this->gamePreview.addCopyVector(list, true);

    this->setupIcons();

    /*std::function<void(void)> resizeHook(
        [&](){
            sf::Vector2f size = this->window.getSize();
            this->back.onResize(size);
            this->arrows.onResize(size);
            this->gamePreview.onResize(size);

            for(int i = 0; i < this->icons.size(); i ++){
                this->icons[i].onResize(size);
            }

        }
    );

    this->window.setOnResize(resizeHook);*/
}

ViewOrchestration::~ViewOrchestration(){
    this->window.close();
}

void ViewOrchestration::displayToWindow(){
    this->window.clear();
    this->back.draw(this->window);
    this->gamePreview.draw(this->window);
    this->arrows.draw(this->window);
    for(int i = 0; i < this->icons.size(); i ++){
        this->icons[i].draw(this->window);
    }
    this->window.display();
}

void ViewOrchestration::tick(){
    this->frameMod = (this->frameMod + 1) % 60;
    this->arrows.tick(this->frameMod, true, true);
    this->gamePreview.tick(this->frameMod);
    // Icons have nothing to tick I guess.
    // But the interface is available.
}

void ViewOrchestration::input(INPUT_FLAG input){
    if(input & INPUT_FLAG::SOMETHING){
        std::cout << "YAY" << std::endl;
    }
}

};
