#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h" // needed?

class Food
{
    public:
        Food(GameMechs* thisGMRef, Player* thisPlayerRef, int numFoods);
        ~Food();
        objPos getFoodPos() const;

        // Student Comment: Food management
        void initializeFoodBin(int numFoods);
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
        

    private:
        GameMechs* mainGameMechsRef;
        Player* playerRef;
        objPos foodPos;
        objPosArrayList* foodBin; // Student Comment: Food bin for storing multiple food items

        // Student Comment: Indices for the special food items
        int specialFoodIndex1;
        int specialFoodIndex2;

        int foodEaten; // Student Comment: Count of food consumed by the player
};

#endif