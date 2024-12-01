#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        // Student Comment: Enumeration for movement directions
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        // Student Comment: Constructor and destructor
        Player(GameMechs* thisGMRef);
        ~Player();

        objPos getPlayerPos() const; // Upgrade this in iteration 3. // Student Comment: Get the head position of the snake     
        void updatePlayerDir(); // Student Comment: Update the direction of the snake based on user input
        void movePlayer(); // Student Comment: Move the snake in the current direction

        // More methods to be added here
        objPosArrayList* getPlayerPosList() const; // Student Comment: Get the list of snake body segments
        void growPlayer(); // Student Comment: Grow the snake by one segment
        void growBy(int length); // Student Comment: Grow the snake by a specified length

    private:
        objPosArrayList* playerPosList; // Student Comment: Tracks all snake body segments   
        enum Dir myDir; // Student Comment: Current movement direction
        GameMechs* mainGameMechsRef; // Student Comment: Reference to game mechanics for interaction
};

#endif