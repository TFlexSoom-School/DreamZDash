#pragma once

/*
 * Tristan Hilbert
 * 2/12/2020
 * Game Preview Header File
 * Use to show previews of games!
 */

#ifndef  DREAMZDASH_GAME_PREVIEW_HPP
#define DREAMZDASH_GAME_PREVIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>
//Ansi Strings
#include <string>

namespace dzdash{

struct GameStruct{
    //Considering making this a pointer
    sf::Uint16 UID;
    sf::Texture cover;
    std::string name;
    std::string author;
};

enum GamePreviewFlags: sf::Uint8{
    //Powers of 2
    GAME_PREV_NONE = 0,

    // CoverArt is cycling to the left (ANIMATION)
    CYCLING_TO_LEFT = 1 << 0,

    // CoverArt is cycling from the left (ANIMATION)
    CYCLING_FROM_LEFT = 1 << 1,

    // Preview is showing spinner because the dashboard must
    //  wait for more games to load.
    WAITING = 1 << 2,

    // Simple Status flag to show a request has been made for more data
    //   This can be checked by governing object/function
    REQUESTING = 1 << 3
};

class GamePreview{
    private:
    std::vector<GameStruct> gamesFirstHalf;
    std::vector<GameStruct> gamesSecondHalf;
    sf::RectangleShape spinner;
    sf::RectangleShape coverArt;
    sf::Text gameNameText;
    sf::Text gameAuthorText;
    sf::Font textFont;
    sf::Uint8 flags;
    sf::Uint8 index;
    sf::Vector2f screenSize;

    private:
    void setup();
    void cycle();
    void resetCoverPos();
    void setTextStrings();
    void setCoverArtText();

    // Tick Helper Functions
    void tick_spinner();
    void tick_coverArtCycleFrom();
    void tick_coverArtCycleTo();

    // Math Helper Function
    const float getCoverArtRestingX();

    public:
    GamePreview();
    virtual ~GamePreview();

    // 2 Ambersands means R-Value Reference
    // Readup !
    // https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
    virtual void addMoveVector(std::vector<GameStruct>&&, bool isAfter = true);

    virtual void addCopyVector(std::vector<GameStruct>&, bool isAfter = true);
    virtual void draw(sf::RenderWindow&);
    virtual void onResize(const sf::Vector2f&);
    virtual void tick(sf::Uint8);

    virtual bool nextGame();
    virtual bool prevGame();

    virtual sf::Uint8 getFlags();
    virtual sf::Uint8 getIndex();
};

};

#endif /* end of include guard: DREAMZDASH_GAME_PREVIEW_HPP */
