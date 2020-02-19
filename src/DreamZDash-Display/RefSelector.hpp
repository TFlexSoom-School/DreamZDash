#pragma once

/*
 * Tristan Hilbert
 * 2/18/2020
 * Dreamzdash ref selector "hash" table Header file
 *
 * Explanation:
 * The idea of this class is to correctly provide references based on a
 * provided grid of UI. This is very possible to do with a matrix and bounds
 * checking. However, I think this could also easily be done with a singular
 * vector/array which concatenates each row. We then would use placeholder
 * objects to control the "index" of the selector. The only rule is to use
 * an n by m rectangular grid, with each row having the same number of blocks.
 */

/*
 * -- Example 1:
 * _______
 *| 3 | 4 |
 *| 2 | X |
 *| 1 | X |
 * -------
 *
 * Would become
 * Cell:  | 1 | X | 2 | X | 3 | 4 |
 * Index: | 0 | 1 | 2 | 3 | 4 | 5 |
 *
 * Each cell would then have a pair with a "Reference"
 *
 * Pair :: FLAG , REF
 * FLAG :: REF_SELECTOR_FLAG(Uint8) flag
 * REF  :: Struct {Vector2f pos, std::function select}
 *
 * -- REF explanation
 * The ref could even be a void* pointer, but this interface shall do us
 * good for now (I don't want to dynamically cast nor make a parent class right
 * now)
 *
 * -- FLAG explanation
 * REF_SELECTOR_FLAG will work with the following:
 * The first nibble (four bits) will be the accepted directions
 * ie - UP || RIGHT || DOWN || LEFT
 * This means you can proceed in this direction to the block. This is in
 * perspective to the index. If LEFT is flagged then the index can move Left
 * into the block.
 *
 * If you're confused try the terminology...
 * "I can proceed _____ into the block"
 *
 * Example 2:
 * 1010 would be accepting up and down, thus you could not enter this blocks
 * from the left and right sides
 *
 * The second nibble is split into 2 parts. The first three bits are the auto
 * direction bits aka the skip bits
 * These will dictate a direction for the index to go when landing on this
 * square
 *
 * ie 000 (0) - Up
 *    001 (1) - Right
 *    010 (2) - Down
 *    011 (3) - Left
 *    101 -> 111 - RESERVED (Don't use these!!!)
 *
 * Consider the example from earlier, the block 1010_100 can be navigated from
 * the top and bottom but will direct the index to the left. This would be a
 * possible value to use for the block next to ref 2 in the top example.
 *
 * the last bit is to show there is a reference attached to the pair.
 * This means the direction bits will be ignored. If the index validly reached
 * this block (ie the accepted directions do not block the selector) then
 * the reference is returned.
 *
 * Thus the complete flag for our example would be 1010_1000
 * An empty reference skip block!
 */


#ifndef DREAMZDASH_REF_SELECTOR_HPP
#define DREAMZDASH_REF_SELECTOR_HPP

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <functional>

namespace dzdash{

// Oh what to do about least sig bit number 4.
enum REF_SELECTOR_FLAG: sf::Uint8{
    ALLOW_ALL_MOVEMENT = 0xF0,
    BLOCK_ALL_MOVEMENT = 0x00,
    ALLOW_UP_MOVEMENT  = 0x80,
    ALLOW_RIGHT_MOVEMENT = 0x40,
    ALLOW_DOWN_MOVEMENT = 0x20,
    ALLOW_LEFT_MOVEMENT = 0x10,
    DIRECT_UP = 0x00,
    DIRECT_RIGHT = 0x02,
    DIRECT_DOWN = 0x04,
    DIRECT_LEFT = 0x06,
    PROVIDE_REFERENCE = 0x01,
    PROVIDE_NO_REFERENCE = 0x00,

    // Bad Values
    // xxxx_0000
    // Use PROVIDE_NO_REFERENCE
    // xxxx_1xxx
    RESERVED = 0x08
};

struct RefSelectorReference{
    sf::Uint8 id;
    sf::Vector2f position;
    std::function<void(void)> select;
};

class RefSelector{
    private:
    std::vector<std::pair<REF_SELECTOR_FLAG, RefSelectorReference>> table;
    int curRow;
    int rowMax;
    unsigned int index;

    private:
    bool isBadFlagValue(REF_SELECTOR_FLAG, bool hasRef = true);
    void checkFlagBounds(REF_SELECTOR_FLAG);

    // Movement
    bool validMove(REF_SELECTOR_FLAG, int);
    void startMoving(REF_SELECTOR_FLAG);

    public:
    RefSelector(int);
    virtual ~RefSelector();

    // Empty Ref Block
    virtual void addBlock(REF_SELECTOR_FLAG);

    // l and r hand references
    virtual void addBlock(
        const std::pair<REF_SELECTOR_FLAG, RefSelectorReference>&
    );

    virtual void addBlock(
        const std::pair<REF_SELECTOR_FLAG, RefSelectorReference>&&
    );

    // Accessors
    virtual sf::Vector2f getPositionOfCurrent();
    virtual sf::Uint8 getUID();

    // Alliases for calling the function
    virtual void select();
    virtual void call();

    // Vector Utilities
    virtual void clear();
    // Int :: New Max Row
    virtual void clear(int);
    virtual void defaultIndex();
    virtual void reserve(int);

    // Movement
    virtual void up();
    virtual void right();
    virtual void down();
    virtual void left();

};


};

#endif /* end of include guard: DREAMZDASH_REF_SELECTOR_HPP */
