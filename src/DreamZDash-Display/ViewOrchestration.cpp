/*
 * Tristan Hilbert
 * 1/30/2020
 * View Orchestration Source File
 *
 */

#include "ViewOrchestration.hpp"
#include "ForeignProcessExchange.hpp"
#include <vector>
#include <iostream>
#include <utility>

namespace dzdash{
// ------- SOURCE FILE CONSTANTS --------
const int number_of_icons = 4;
const int battery_index = 0;
const int settings_index = 1;
const int wifi_index = 2;
const int power_index = 3;

const sf::Uint8 selector_power_id = 0;
const sf::Uint8 selector_battery_id = 1;
const sf::Uint8 selector_game_preview_id = 2;
const sf::Uint8 selector_settings_id = 3;
const sf::Uint8 selector_wifi_id = 4;

// ------- PRIVATE FUNCTIONS ---------
void ViewOrchestration::setupIcons(){
    // Since the icons will copy the textures
    //    we can allocate them on the stack
    sf::Texture textTemp;

    // Constants to do math off of
    const int iDim = 64;
    const float fDim = iDim;
    const float fDimHalf = fDim / 2.0f;

    // Get space for these sprites
    this->icons.reserve(number_of_icons);
    // Create a icon rect for each icon. This will be a blank rect of size
    //   iDim, iDim
    this->icons.assign(number_of_icons, Icon(sf::Vector2f(iDim, iDim)));


    // Battery Status Icon
    textTemp.loadFromFile("./assets/full_battery.png");
    /*
     * TODO
     * When we actually load this in, we should add to the texture
     * to create a sprite map for the different batteries.
     * The textTemp object can do that here.
     *
     */
    this->icons[battery_index].setPosition(sf::Vector2f(
        defaultRatio.x * 5.0f / 6.0f,
        defaultRatio.y * 11.0f / 12.0f - fDimHalf
    ));
    this->icons[battery_index].copySetText(textTemp);

    // Settings Icon
    textTemp.loadFromFile("./assets/settings.png");
    this->icons[settings_index].setPosition(sf::Vector2f(
        defaultRatio.x / 12.0f,
        defaultRatio.y / 36.0f
    ));
    this->icons[settings_index].copySetText(textTemp);

    // Wifi icon
    // Might want a better picture
    textTemp.loadFromFile("./assets/external.png");
    this->icons[wifi_index].setPosition(sf::Vector2f(
        defaultRatio.x * 5.0f / 6.0f,
        defaultRatio.y / 36.0f
    ));
    this->icons[wifi_index].copySetText(textTemp);

    // Power Button Icon
    // Might want a better picture
    textTemp.loadFromFile("./assets/plus.png");
    this->icons[power_index].setPosition(sf::Vector2f(
        defaultRatio.x / 2.0f - fDimHalf / 2.0f,
        defaultRatio.y * 11.0f / 12.0f - fDimHalf
    ));
    this->icons[power_index].copySetText(textTemp);
}

void ViewOrchestration::setupSelector(){
    /*
     * -- Example 1:
     * _______
     *| 4 | 5 |
     *| 3 | X |
     *| 1 | 2 |
     * -------
     */

    // Rows - 3
    // Cols - 2
    // Grid Size = 3 * 2
    this->selectorData.reserve(3 * 2);

    // Don't use a temp variable to make use of r value ref optimization

    // Block 1
    this->selectorData.addBlock(
        std::pair<REF_SELECTOR_FLAG, RefSelectorReference>(
            (
                static_cast<REF_SELECTOR_FLAG>(
                    REF_SELECTOR_FLAG::ALLOW_DOWN_MOVEMENT |
                    REF_SELECTOR_FLAG::ALLOW_LEFT_MOVEMENT |
                    REF_SELECTOR_FLAG::PROVIDE_REFERENCE
                )
            ),
            (RefSelectorReference){
                selector_power_id,
                this->icons[power_index].getPosition(),
                [](){} // Empty Function
            }
        )
    );

    // Block 2
    this->selectorData.addBlock(
        std::pair<REF_SELECTOR_FLAG, RefSelectorReference>(
            (
                static_cast<REF_SELECTOR_FLAG>(
                    REF_SELECTOR_FLAG::ALLOW_DOWN_MOVEMENT |
                    REF_SELECTOR_FLAG::ALLOW_RIGHT_MOVEMENT |
                    REF_SELECTOR_FLAG::PROVIDE_REFERENCE
                )
            ),
            (RefSelectorReference){
                selector_battery_id,
                this->icons[battery_index].getPosition(),
                [](){} // Empty Function
            }
        )
    );

    // Block 3
    this->selectorData.addBlock(
        std::pair<REF_SELECTOR_FLAG, RefSelectorReference>(
            (
                static_cast<REF_SELECTOR_FLAG>(
                    REF_SELECTOR_FLAG::ALLOW_UP_MOVEMENT |
                    REF_SELECTOR_FLAG::ALLOW_LEFT_MOVEMENT |
                    REF_SELECTOR_FLAG::ALLOW_DOWN_MOVEMENT |
                    REF_SELECTOR_FLAG::PROVIDE_REFERENCE
                )
            ),
            (RefSelectorReference){
                selector_game_preview_id,
                sf::Vector2f(
                    this->window.getSize().x / 2.0f,
                    this->window.getSize().y / 2.0f
                ),
                [&](){
                    execute_game("");
                    this->window.close();
                }
            }
        )
    );

    // Block X
    this->selectorData.addBlock(
        static_cast<REF_SELECTOR_FLAG>(
            REF_SELECTOR_FLAG::ALLOW_UP_MOVEMENT |
            REF_SELECTOR_FLAG::ALLOW_DOWN_MOVEMENT |
            REF_SELECTOR_FLAG::DIRECT_LEFT |
            REF_SELECTOR_FLAG::PROVIDE_NO_REFERENCE
        )
    );

    // Block 4
    this->selectorData.addBlock(
        std::pair<REF_SELECTOR_FLAG, RefSelectorReference>(
            (
                static_cast<REF_SELECTOR_FLAG>(
                    REF_SELECTOR_FLAG::ALLOW_LEFT_MOVEMENT |
                    REF_SELECTOR_FLAG::ALLOW_UP_MOVEMENT |
                    REF_SELECTOR_FLAG::PROVIDE_REFERENCE
                )
            ),
            (RefSelectorReference){
                selector_settings_id,
                this->icons[settings_index].getPosition(),
                [](){} // Empty Function
            }
        )
    );

    // Block 5
    this->selectorData.addBlock(
        std::pair<REF_SELECTOR_FLAG, RefSelectorReference>(
            (
                static_cast<REF_SELECTOR_FLAG>(
                    REF_SELECTOR_FLAG::ALLOW_RIGHT_MOVEMENT |
                    REF_SELECTOR_FLAG::ALLOW_UP_MOVEMENT |
                    REF_SELECTOR_FLAG::PROVIDE_REFERENCE
                )
            ),
            (RefSelectorReference){
                selector_wifi_id,
                this->icons[wifi_index].getPosition(),
                [](){} // Empty Function
            }
        )
    );

    // Set a custom destination example for blueSquareSelector
    this->blueSquareSelector.setDestination(
        this->selectorData.getPositionOfCurrent()
    );
}


bool ViewOrchestration::inputLeftRight(bool isLeft){
    if(this->selectorData.getUID() == selector_game_preview_id){
        // TODO Bugged! Test and Fix GamePreview!
        if(isLeft){
            //this->gamePreview.nextGame();
        }else{
            //this->gamePreview.prevGame();
        }
        return false;
    }else{
        if(isLeft){
            this->selectorData.left();
        }else{
            this->selectorData.right();
        }
        return true;
    }
}




// ------- PUBLIC FUNCTIONS ----------

ViewOrchestration::ViewOrchestration():
    window(),
    back(),
    arrows(),
    blueSquareSelector(),
    selectorData(2),
    gamePreview(),
    icons(),
    frameMod(0)
{

    // Create Example Game List!
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

    // Create Icons based on Loaded Art Assets
    this->setupIcons();

    // Create Referense Selector Data Structure
    this->setupSelector();


    // TODO Still Bugged
    // Needs more Testing (and Cowbell)
    std::function<void(void)> resizeHook(
        [&](){
            sf::Vector2u size = this->window.getSize();
            sf::Vector2f sizef = sf::Vector2f(size.x, size.y);
            this->back.onResize(sizef);
            this->arrows.onResize(sizef);
            this->blueSquareSelector.onResize(sizef);
            this->gamePreview.onResize(sizef);

            for(int i = 0; i < this->icons.size(); i ++){
                this->icons[i].onResize(sizef);
            }

            std::cout << "RESIZE!!" << std::endl;

        }
    );
    //this->window.setOnResize(resizeHook);
}

ViewOrchestration::~ViewOrchestration(){
    this->window.close();
}

void ViewOrchestration::displayToWindow(){
    this->window.clear();
    this->back.draw(this->window);
    this->blueSquareSelector.draw(this->window);
    this->gamePreview.draw(this->window);
    this->arrows.draw(this->window);
    for(int i = 0; i < this->icons.size(); i ++){
        this->icons[i].draw(this->window);
    }
    this->window.display();
}

void ViewOrchestration::tick(){
    this->frameMod = (this->frameMod + 1) % 60;
    this->blueSquareSelector.tick(this->frameMod);
    this->arrows.tick(this->frameMod, this->gamePreview.getIndex(), 5);
    this->gamePreview.tick(this->frameMod);
    // Icons have nothing to tick I guess.
    // But the interface is available.
}

void ViewOrchestration::input(INPUT_FLAG input){
    bool updateDest = false;
    switch(input){
        case INPUT_UP:
            this->selectorData.up();
            updateDest = true;
            break;
        case INPUT_RIGHT:
            updateDest = this->inputLeftRight(false);
            break;
        case INPUT_DOWN:
            this->selectorData.down();
            updateDest = true;
            break;
        case INPUT_LEFT:
            updateDest = this->inputLeftRight(true);
            break;
        case INPUT_SELECT:
            this->selectorData.select();
            break;
        default:
            break;
    }

    if(updateDest){
        this->blueSquareSelector.setDestination(
            this->selectorData.getPositionOfCurrent()
        );
    }
}

};
