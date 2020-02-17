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

ViewOrchestration::ViewOrchestration():
    window(),
    back(),
    arrows(),
    gamePreview(),
    frameMod(0)
{
    std::vector<GameStruct> list;
    list.reserve(5);

    sf::Texture text;
    text.loadFromFile("./freelancer.jpg");
    GameStruct temp = {0, text, "Some Guy\nNamed Tristan", "TFlexSoom"};

    for(int i = 0; i < 5; i ++){
        list.push_back(temp);
        temp.UID += 1;
        temp.name += "r";
    }

    this->gamePreview.addCopyVector(list, true);

    /*std::function<void()> resizeHook(
        [&](){
            sf::Vector2f size = this->window.getSize();
            this->back.onResize(size);
            this->arrows.onResize(size);
            this->gamePreview.onResize(size);
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
    this->window.display();
}

void ViewOrchestration::tick(){
    this->frameMod = (this->frameMod + 1) % 60;
    this->arrows.tick(this->frameMod, true, true);
    this->gamePreview.tick(this->frameMod);
}

void ViewOrchestration::input(INPUT_FLAG input){
    if(input & INPUT_FLAG::SOMETHING){
        std::cout << "YAY" << std::endl;
    }
}

};
