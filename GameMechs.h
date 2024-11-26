#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        /* Student Comment: Destructor is empty because there is no
        dynamically allocated resources or heap based pointers in the GameMechs class.
        The destructor is not strictly needed but it can be removed without issues
        because no custom cleanup logic is required, and the default compiler-generated
        destructor will be enough. */
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const; // USER ADDED COMMENT: should remove const keyword?
        // Student Comment: The const keyword should remain. It is appropriate for getter methods
        // and aligns with best practices as it ensures the method does not inadvertently modify the object

        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore();
        
        // More methods should be added here
        objPos getFood() const;
        void generateFood(const objPosArrayList& snakeBody);
        
};

#endif