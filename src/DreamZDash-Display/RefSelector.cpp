/*
 * Tristan Hilbert
 * 2/18/2020
 * RefSelector Source file
 * See Header File for Explanation
 *
 */


#include "RefSelector.hpp"
#include <stdexcept>
#include <string>

namespace dzdash{
    const RefSelectorReference emptyRef = {
        sf::Uint8(0xFF),
        sf::Vector2f(0,0),
        [](){}
    };

    RefSelector::RefSelector(int rowMax):
        table(),
        curRow(0),
        rowMax(rowMax),
        index(0)
    {

    }

    RefSelector::~RefSelector(){ }

    bool RefSelector::isBadFlagValue(REF_SELECTOR_FLAG flag, bool hasRef){\
        // Uses bad bit xxxx1xxx
        if(flag & REF_SELECTOR_FLAG::RESERVED){
            return true;
        }

        // Uses Illegal bits xxxx0000
        if((flag & ~REF_SELECTOR_FLAG::ALLOW_ALL_MOVEMENT) == 0){
            return true;
        }

        // Should not have a ref but flag says it does
        if((flag & REF_SELECTOR_FLAG::PROVIDE_REFERENCE) && hasRef == false){
            return true;
        // Has a ref but flag says it does not
        }else if((
            (flag & REF_SELECTOR_FLAG::PROVIDE_REFERENCE) == 0) &&
            hasRef == true
        ){
            return true;
        }

        return false;
    }

    void RefSelector::checkFlagBounds(REF_SELECTOR_FLAG val){
        // Do not break walls of grid
        if(this->curRow == 0){
            if(val & REF_SELECTOR_FLAG::ALLOW_RIGHT_MOVEMENT){
                throw std::invalid_argument(
                    std::string("For ending row blocks,") +
                    std::string("please disallow LEFT_MOVEMENT\n") +
                    std::string("Block: ") +
                    std::to_string(this->table.size() + 1)
                );
            }
        }else if(this->curRow + 1 == this->rowMax){
            if(val & REF_SELECTOR_FLAG::ALLOW_LEFT_MOVEMENT){
                throw std::invalid_argument(
                    std::string("For ending row blocks,") +
                    std::string("please disallow RIGHT_MOVEMENT\n") +
                    std::string("Block: ") +
                    std::to_string(this->table.size() + 1)
                );
            }
        }

        this->curRow += 1;
        this->curRow %= this->rowMax;
    }

    bool RefSelector::validMove(REF_SELECTOR_FLAG val, int index){
        if(index < 0 || index > table.size()){
            return false;
        }

        // Translate DIRECT counter to ALLOW flag bits
        switch(val){
            case REF_SELECTOR_FLAG::DIRECT_UP:
                val = REF_SELECTOR_FLAG::ALLOW_UP_MOVEMENT;
                break;
            case REF_SELECTOR_FLAG::DIRECT_RIGHT:
                val = REF_SELECTOR_FLAG::ALLOW_RIGHT_MOVEMENT;
                break;
            case REF_SELECTOR_FLAG::DIRECT_DOWN:
                val = REF_SELECTOR_FLAG::ALLOW_DOWN_MOVEMENT;
                break;
            case REF_SELECTOR_FLAG::DIRECT_LEFT:
                val = REF_SELECTOR_FLAG::ALLOW_LEFT_MOVEMENT;
                break;
            default:
                val = REF_SELECTOR_FLAG::PROVIDE_NO_REFERENCE;
                break;
        }

        return val & this->table[index].first;
    }

    // Call this with the DIRECT(ION) flags
    void RefSelector::startMoving(REF_SELECTOR_FLAG dir){
        int scanIndex = this->index;
        bool safeMove = true;

        do{
            // We only want directions least sig bits
            // dir &= 0x06
            dir = static_cast<REF_SELECTOR_FLAG>(
                    dir & REF_SELECTOR_FLAG::DIRECT_LEFT
                );

            switch(dir){
                case REF_SELECTOR_FLAG::DIRECT_UP:
                    scanIndex += this->rowMax;
                    break;
                case REF_SELECTOR_FLAG::DIRECT_RIGHT:
                    scanIndex += 1;
                    break;
                case REF_SELECTOR_FLAG::DIRECT_DOWN:
                    scanIndex -= this->rowMax;
                    break;
                case REF_SELECTOR_FLAG::DIRECT_LEFT:
                    scanIndex -= 1;
                    break;
                default:
                    safeMove = false;
                    break;
            }

            if(!validMove(dir, scanIndex)){
                safeMove = false;
            }else{
                dir = this->table[scanIndex].first;
                if(dir & PROVIDE_REFERENCE){
                    break;
                }
            }

        // Here is some safety, but we can't solve the Halting Problem
        // "scanIndex != this->index" => No Looping
        // However a loop can still be created :( (We cannot detect state entry)
        }while(safeMove && scanIndex != this->index);


        if(safeMove){
            this->index = scanIndex;
        }
    }

    void RefSelector::addBlock(REF_SELECTOR_FLAG val){
        // No Bad Flag Value
        if(isBadFlagValue(val, false)){
            throw std::invalid_argument("Flag has bad value!");
        }

        checkFlagBounds(val);

        // Use Reserve to better optimize this process!
        this->table.push_back(
            std::pair<REF_SELECTOR_FLAG, RefSelectorReference>(val, emptyRef)
        );
    }

    void RefSelector::addBlock(
        const std::pair<REF_SELECTOR_FLAG, RefSelectorReference>& val
    ){
        // No Bad Flag Value
        if(isBadFlagValue(val.first, true)){
            throw std::invalid_argument("Flag has bad value!");
        }

        checkFlagBounds(val.first);

        // Use Reserve Call to better optimize this process!
        this->table.push_back(
            std::pair<REF_SELECTOR_FLAG, RefSelectorReference>(
                val.first,
                val.second
            )
        );
    }

    void RefSelector::addBlock(
        const std::pair<REF_SELECTOR_FLAG, RefSelectorReference>&& val
    ){
        // No Bad Flag Value
        if(isBadFlagValue(val.first, true)){
            throw std::invalid_argument("Flag has bad value!");
        }

        checkFlagBounds(val.first);

        // Use Reserve Call to better optimize this process!
        this->table.push_back(
            std::pair<REF_SELECTOR_FLAG, RefSelectorReference>(
                val.first,
                val.second
            )
        );
    }

    sf::Vector2f RefSelector::getPositionOfCurrent(){
        if(this->index < this->table.size()){
            return this->table[this->index].second.position;
        }

        return sf::Vector2f(0,0);
    }

    sf::Uint8 RefSelector::getUID(){
        if(this->index < this->table.size()){
            return this->table[this->index].second.id;
        }

        return 0;
    }

    void RefSelector::select(){
        if(this->index < this->table.size()){
            this->table[this->index].second.select();
        }
    }

    void RefSelector::call(){
        select();
    }

    void RefSelector::clear(){
        this->table.clear();
        this->curRow = 0;
        this->index = 0;
    }

    void RefSelector::clear(int rowMax){
        this->rowMax = rowMax;
        this->clear();
    }

    void RefSelector::defaultIndex(){
        this->index = 0;
    }

    void RefSelector::reserve(int capacity){
        if(this->table.size() < capacity){
            this->table.reserve(capacity);
        }
    }

    void RefSelector::up(){
        startMoving(REF_SELECTOR_FLAG::DIRECT_UP);
    }
    void RefSelector::right(){
        startMoving(REF_SELECTOR_FLAG::DIRECT_RIGHT);
    }
    void RefSelector::down(){
        startMoving(REF_SELECTOR_FLAG::DIRECT_DOWN);
    }
    void RefSelector::left(){
        startMoving(REF_SELECTOR_FLAG::DIRECT_LEFT);
    }
};
