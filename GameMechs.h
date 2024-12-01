#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

class Player;

using namespace std;

class GameMechs
{
    private:
        char input; // Student Comment: Last user input character
        bool exitFlag; // Student Comment: Flag to indicate game exit
        bool loseFlag; // Student Comment: Flag to indicate game over condition
        int score; // Student Comment: Current player score

        // Student Comment: Game board dimensions
        int boardSizeX;
        int boardSizeY;

        objPos food; // Student Comment: Current food object
        objPosArrayList foodBin; // Student Comment: Food bin for storing multiple food items
        
        // Student Comment: Indices for the special food items
        int specialFoodIndex1;
        int specialFoodIndex2;

        int foodEaten; // Student Comment: Count of food consumed by the player

    public:
        // Student Comment: Constructors and destructor
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        /* Student Comment: Destructor is empty because there is no
        dynamically allocated resources or heap based pointers in the GameMechs class.
        The destructor is not strictly needed but it can be removed without issues
        because no custom cleanup logic is required, and the default compiler-generated
        destructor will be enough. */
        
        // Student Comment: Getters and setters
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
        void incrementScoreBy(int points);
        
        // More methods should be added here
        // Student Comment: Food management
        objPos getFood() const;
        void generateFood(const objPosArrayList& snakeBody);
        void initializeFoodBin(int numFoods = 5);
        objPosArrayList* getFoodBin() const;
        void regenerateFoodAt(int index, const objPosArrayList& snakeBody);

        // Student Comment: Special food effects
        void applySpecialFoodEffect(int index, Player* player);
        void regenerateAllFood(const objPosArrayList& snakeBody);
        void regenerateSpecialFoods(const objPosArrayList& snakeBody);

        // Student Comment: Food-related stats
        int getFoodEaten() const;
        void incrementFoodEaten();

        int getSpecialFoodIndex1() const;
        int getSpecialFoodIndex2() const;
};

#endif