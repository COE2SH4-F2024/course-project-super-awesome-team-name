#include "Food.h"
#include "time.h"

#include "MacUILib.h"

Food::Food(GameMechs* thisGMRef, Player* thisPlayerRef, int numFoods)
{
    mainGameMechsRef = thisGMRef;
    playerRef = thisPlayerRef;
    srand(time(NULL)); // Student Comment: Seed RNG
    foodEaten = 0;
    specialFoodIndex1 = 0;
    specialFoodIndex2 = 1;
    objPos foodPos;
    foodBin = new objPosArrayList(numFoods); // Student Comment: Food bin for storing multiple food items

    initializeFoodBin(numFoods);
}

Food::~Food()
{
    
}

// Student Comment: Food management
objPos Food::getFoodPos() const
{
    return foodPos;
}

int Food::getFoodEaten() const
{
    return foodEaten;
}

int Food::getSpecialFoodIndex1() const
{
    return specialFoodIndex1;
}

int Food::getSpecialFoodIndex2() const
{
    return specialFoodIndex2;
}

void Food::incrementFoodEaten()
{
    foodEaten++;
}

// Student Comment: Initializes the food bin with multiple food items
void Food::initializeFoodBin(int numFoods)
{
    for (int i = 0; i < numFoods; i++)
    {
        objPos food(0, 0, 0);
        foodBin->insertTail(food);
        regenerateFoodAt(i, *playerRef->getPlayerPosList());
    }
}

// Student Comment: Returns a pointer to the food bin
objPosArrayList* Food::getFoodBin() const
{
    return foodBin;
}

// Student Comment: Regenerates a specific food item ensuring no overlap with the snake or other food items
void Food::regenerateFoodAt(int index, const objPosArrayList& snakeBody)
{
    if (index < 0 || index >= foodBin->getSize())
    {
        return;
    }

    bool validPosition = false;
    int x, y;

    while (!validPosition)
    {
        x = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 2);
        y = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 2);

        validPosition = true;

        // Student Comment: Check against snake body
        for (int i = 0; i < snakeBody.getSize(); i++)
        {
            objPos snakeSegment = snakeBody.getElement(i);
            if (snakeSegment.pos->x == x && snakeSegment.pos->y == y)
            {
                validPosition = false;
                break;
            }
        }

        // Student Comment: Check against other food items
        if (validPosition)
        {
            for (int i = 0; i < foodBin->getSize(); i++)
            {
                if (i == index) continue;
                objPos existingFood = foodBin->getElement(i);
                if (existingFood.pos->x == x && existingFood.pos->y == y)
                {
                    validPosition = false;
                    break;
                }
            }
        }
    }

    char symbol = '*';
    if (index == specialFoodIndex1 || index == specialFoodIndex2)
    {
        symbol = '$';
    }

    objPos newFood(x, y, symbol);

    // Alternative to setElement() in case the implementation is not allowed:
    // objPos food = foodBin->getElement(index);
    // food.setObjPos(x, y, symbol);

    foodBin->setElement(index, newFood);
}

// Student Comment: Applies effects of special food and regenerates it
void Food::applySpecialFoodEffect(int index, Player* player)
{
    if (index == specialFoodIndex1)
    {
        mainGameMechsRef->incrementScoreBy(10);
        regenerateAllFood(*playerRef->getPlayerPosList());
    }
    else if (index == specialFoodIndex2)
    {
        mainGameMechsRef->incrementScoreBy(50);
        regenerateSpecialFoods(*playerRef->getPlayerPosList());
        player->growBy(10);
    }

    regenerateFoodAt(index, *player->getPlayerPosList());
}

// Student Comment: Regenerates all food items
void Food::regenerateAllFood(const objPosArrayList& snakeBody)
{
    for (int i = 0; i < foodBin->getSize(); i++)
    {
        regenerateFoodAt(i, snakeBody);
    }
}

// Student Comment: Regenerates only the special food items
void Food::regenerateSpecialFoods(const objPosArrayList& snakeBody)
{
    regenerateFoodAt(specialFoodIndex1, snakeBody);
    regenerateFoodAt(specialFoodIndex2, snakeBody);
}