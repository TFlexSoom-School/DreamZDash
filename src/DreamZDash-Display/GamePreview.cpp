/*
 * Tristan Hilbert
 * 2/12/2020
 * Game Preview Source File
 *
 */

// All Debian Distros:
// Font /usr/share/fonts/truetype/liberation/Liberation-Bold.ttf

/*
private:
std::Vector<GameStruct> gamesFirstHalf;
std::Vector<GameStruct> gamesSecondHalf;
sf::RectangleShape spinner;
sf::RectangleShape coverArt;
sf::Text gameNameText;
sf::Text gameAuthorText;
sf::Uint8 flags;
sf::Uint8 index;
*/

#include "GamePreview.hpp"
#include "Constants.hpp"
#include <stdexcept>
#include <utility>
#include <iostream>

namespace dzdash{

const float spinnerDefault_x = defaultRatio.x / 32.0f;
const float spinnerDefault_y = defaultRatio.y / 24.0f;

const float coverArtDefault_x = defaultRatio.x / 4.0f;
const float coverArtDefault_y = defaultRatio.y / 2.0f;

//Constructor:
GamePreview::GamePreview():
    gamesFirstHalf(0),
    gamesSecondHalf(0),
    spinner(sf::Vector2f(spinnerDefault_x, spinnerDefault_y)),
    coverArt(sf::Vector2f(coverArtDefault_x, coverArtDefault_y)),
    gameNameText(),
    gameAuthorText(),
    textFont(),
    flags(0),
    index(0),
    screenSize(defaultRatio)
{
    this->setup();
}

GamePreview::~GamePreview(){ }

/* ---- PRIVATE FUNCTIONS ---- */
void GamePreview::setup(){
    this->spinner.setPosition(sf::Vector2f(
        this->screenSize.x / 2.0f,
        this->screenSize.y / 2.0f
    ));

    this->resetCoverPos();

    if(this->textFont.loadFromFile(defaultFontPath) == false){
        throw new std::runtime_error("File " + defaultFontPath +
            " cannot be loaded"
        );
    }

    this->gameNameText.setFont(textFont);
    this->gameAuthorText.setFont(textFont);

    this->gameNameText.setCharacterSize(32);
    this->gameAuthorText.setCharacterSize(20);

    this->gameNameText.setPosition(sf::Vector2f(
        this->screenSize.x / 9.0f * 5.0f,
        this->screenSize.y / 2.0f
    ));

    std::cout << this->gameNameText.getLocalBounds().height << std::endl;

    this->gameAuthorText.setPosition(sf::Vector2f(
        this->screenSize.x / 9.0f * 5.0f,
        this->screenSize.y / 8.0f * 5.0f
    ));

    this->flags = GamePreviewFlags::REQUESTING;
    this->flags |= GamePreviewFlags::WAITING;
}

void GamePreview::cycle(){
    // Take care of Image Transition
    const int sizeFirst = this->gamesFirstHalf.size();
    const int sizeSecond = this->gamesSecondHalf.size();
    if(this->index > 0 && this->index < sizeFirst){
        this->coverArt.setTexture(&this->gamesFirstHalf[this->index].cover);
    }else if(this->index > sizeFirst && this->index < sizeSecond){
        this->coverArt.setTexture(
            &this->gamesSecondHalf[this->index - sizeFirst].cover
        );
    }

    // Set Position No Matter What
    this->resetCoverPos();

    this->flags=GamePreviewFlags::CYCLING_TO_LEFT;
}

void GamePreview::resetCoverPos(){
    // Default Position
    this->coverArt.setPosition(sf::Vector2f(
        this->getCoverArtRestingX(),
        this->screenSize.y / 4.0f
    ));

}

void GamePreview::setTextStrings(){
    const int firstSize = this->gamesFirstHalf.size();

    if(this->index < firstSize){

        this->gameNameText.setString(
            this->gamesFirstHalf[this->index].name
        );

        this->gameAuthorText.setString(
            this->gamesFirstHalf[this->index].author
        );

    }else{

        this->gameNameText.setString(
            this->gamesSecondHalf[this->index - firstSize].name
        );

        this->gameAuthorText.setString(
            this->gamesSecondHalf[this->index - firstSize].author
        );

    }
}


void GamePreview::setCoverArtText(){
    const int firstSize = this->gamesFirstHalf.size();

    if(this->index < firstSize){
        this->coverArt.setTexture(
                &this->gamesFirstHalf[this->index].cover
        );

    }else{
        this->coverArt.setTexture(
                &this->gamesSecondHalf[this->index - firstSize].cover
        );
    }
}

/* ---- TICK HELPER PRIVATE FUNCTIONS ---- */
void GamePreview::tick_spinner(){
    this->spinner.rotate(5.0f);
}

void GamePreview::tick_coverArtCycleFrom(){
    this->coverArt.move(sf::Vector2f(-20.0f, 0.0f));
    if(this->coverArt.getPosition().x < -1.0f * this->coverArt.getSize().x){
        this->coverArt.setPosition(sf::Vector2f(
            this->screenSize.x + this->coverArt.getSize().x,
            this->coverArt.getPosition().y
        ));

        this->flags &= (~GamePreviewFlags::CYCLING_TO_LEFT);
        this->flags |= GamePreviewFlags::CYCLING_FROM_LEFT;
    }
}

void GamePreview::tick_coverArtCycleTo(){
    this->coverArt.move(sf::Vector2f(-20.0f, 0.0f));
    if(this->coverArt.getPosition().x < this->getCoverArtRestingX()){
        this->resetCoverPos();
        this->flags &= (~GamePreviewFlags::CYCLING_FROM_LEFT);
    }
}

/* ---- MATH HELPER FUNCTIONS ---- */

const float GamePreview::getCoverArtRestingX(){
    return this->screenSize.x / 9.0f * 2.0f;
}


/* ---- PUBLIC FUNCTIONS ---- */
void GamePreview::addMoveVector(std::vector<GameStruct>&& r, bool isAfter){
    if(isAfter){
        // Index Safety to still point to same game
        if(this->index > this->gamesFirstHalf.size()){
            this->index -= this->gamesFirstHalf.size();
        }else{
            // This case should only occur on first addition
            //    bad case to reach otherwise.
            this->index = 0;
        }

        // Delete FirstHalf Vector and move
        this->gamesFirstHalf = std::move(this->gamesSecondHalf);
        //Add Second Half
        this->gamesSecondHalf = std::move(r);


    }else{
        // Index Safety to still point to same game
        if(this->index < this->gamesFirstHalf.size()){
            this->index += r.size();
        }else{
            // This case should only occur on first addition
            //    bad case to reach otherwise.
            this->index = 0;
        }

        // Delete SecondHalf Vector and move
        this->gamesSecondHalf = std::move(this->gamesFirstHalf);
        // Add First Half
        this->gamesFirstHalf = std::move(r);
    }
    // No longer requesting
    this->flags &= ~GamePreviewFlags::REQUESTING;
    this->flags &= ~GamePreviewFlags::WAITING;
}

void GamePreview::addCopyVector(std::vector<GameStruct>& r, bool isAfter){
    if(isAfter){
        // Index Safety to still point to same game
        if(this->index > this->gamesFirstHalf.size()){
            this->index -= this->gamesFirstHalf.size();
        }else{
            // This case should only occur on first addition
            //    bad case to reach otherwise.
            this->index = 0;
        }

        // Delete FirstHalf Vector and move
        this->gamesFirstHalf = this->gamesSecondHalf;
        // Add Second Half
        this->gamesSecondHalf = r;


    }else{
        // Index Safety to still point to same game
        if(this->index < this->gamesFirstHalf.size()){
            this->index += r.size();
        }else{
            // This case should only occur on first addition
            //    bad case to reach otherwise.
            this->index = 0;
        }

        // Delete SecondHalf Vector and move
        this->gamesSecondHalf = this->gamesFirstHalf;
        //Add First Half
        this->gamesFirstHalf = r;
    }
    // No longer requesting
    this->flags &= ~GamePreviewFlags::REQUESTING;
    this->flags &= ~GamePreviewFlags::WAITING;
}

void GamePreview::draw(sf::RenderWindow& window){
    if(this->flags & GamePreviewFlags::WAITING){
        window.draw(this->spinner);
    }else{
        window.draw(this->coverArt);

        // Don't Draw when coverArt is animated
        if((this->flags & (
            GamePreviewFlags::CYCLING_TO_LEFT |
            GamePreviewFlags::CYCLING_FROM_LEFT
        )) == GamePreviewFlags::GAME_PREV_NONE)
        {
            window.draw(this->gameNameText);
            window.draw(this->gameAuthorText);
        }

    }
}

void GamePreview::onResize(const sf::Vector2f& size){
    this->screenSize = size;
    this->spinner.setSize(sf::Vector2f(
        this->screenSize.x / 32.0f,
        this->screenSize.y / 24.0f
    ));

    this->spinner.setPosition(sf::Vector2f(
        this->screenSize.x / 2.0f,
        this->screenSize.y / 2.0f
    ));

    this->coverArt.setSize(sf::Vector2f(
        this->screenSize.x / 8.0f,
        this->screenSize.y / 2.4f
    ));

    this->resetCoverPos();

    // TODO Increase Font Size based on new size

    this->gameNameText.setPosition(sf::Vector2f(
        this->screenSize.x / 3.0f * 2.0f,
        this->screenSize.y / 2.0f
    ));

    this->gameAuthorText.setPosition(sf::Vector2f(
        this->screenSize.x / 3.0f * 2.0f,
        this->screenSize.y / 2.0f + this->gameNameText.getLocalBounds().height
    ));

    this->flags = GamePreviewFlags::WAITING;
}

void GamePreview::tick(sf::Uint8 frameMod){
    if(this->flags & GamePreviewFlags::WAITING){
        this->tick_spinner();
    }

    // There might be a weird timing issue where the spinner
    // finishes waiting while the cover is cycling.
    // I'll leave this as a bug that can be fixed here.
    if(this->flags & GamePreviewFlags::CYCLING_TO_LEFT){
        // It should not be both cycling FROM LEFT and TO LEFT
        this->flags &= ~GamePreviewFlags::CYCLING_FROM_LEFT;
        this->tick_coverArtCycleTo();

        // Cycle From left when new games are ready.
    }else if(
        this->flags & GamePreviewFlags::CYCLING_FROM_LEFT &&
        (this->flags & GamePreviewFlags::WAITING) == 0
    ){
        this->tick_coverArtCycleFrom();
    }else{
        this->setCoverArtText();
        this->setTextStrings();
    }
}

bool GamePreview::nextGame(){
    const int firstSize = this->gamesFirstHalf.size();
    const int firstSizeAndHalfSecond =
        firstSize + (this->gamesSecondHalf.size() / 2);

    const int sizeTotal = firstSize + this->gamesSecondHalf.size();

    if(this->index <  sizeTotal - 1){
        this->index += 1;
        this->setTextStrings();
    }else if(this->index == sizeTotal - 1){
        // If we reach the end of the game list start spinning
        this->index += 1;
        this->flags |= GamePreviewFlags::WAITING;
        this->flags |= GamePreviewFlags::REQUESTING;
        return true;
    }

    this->cycle(); // Dependent on this->index

    if(this->index > firstSizeAndHalfSecond){// If we are close to the end of the game list request another
        //    list of games.
        this->flags |= GamePreviewFlags::REQUESTING;
        return true;
    }

    this->flags &= ~GamePreviewFlags::WAITING;
    return false;
}

bool GamePreview::prevGame(){
    const int firstSize = this->gamesFirstHalf.size();

    if(index > 0){
        index -= 1;
        this->setTextStrings();
    }else if(this->index == 0){
        // If we reach the end of the game list start spinning
        index -= 1;
        this->flags |= GamePreviewFlags::WAITING;
        this->flags |= GamePreviewFlags::REQUESTING;
        return true;
    }

    this->cycle(); // Dependent on this->index

    if(index < gamesFirstHalf.size() / 2){
        // If we are close to the end of the game list request another
        //    list of games.
        this->flags |= GamePreviewFlags::REQUESTING;
        return true;
    }

    this->flags &= ~GamePreviewFlags::WAITING;
    return false;
}

sf::Uint8 GamePreview::getFlags(){
    return this->flags;
}

sf::Uint8 GamePreview::getIndex(){
    return this->index;
}

};
