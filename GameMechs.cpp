#include "GameMechs.h"
#include "Player.h"

// Student Comment: Default constructor initializes game mechanics and random number generator
GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

    // srand(static_cast<unsigned int>(time(0))); // Student Comment: Seed RNG
    // foodEaten = 0;
    // specialFoodIndex1 = 0;
    // specialFoodIndex2 = 1;
}

// Student Comment: Constructor with custom board size
GameMechs::GameMechs(int boardX, int boardY)
{
    // GameMechs();
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    // foodEaten = 0;
    // srand(static_cast<unsigned int>(time(0))); // Student Comment: Seed RNG
    // specialFoodIndex1 = 0;
    // specialFoodIndex2 = 1;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // no pointers/heap data members
    
    // Student Comment: The destructor is empty because the class
    // has no dynamic memory management, meaning the destructor could be safely removed.
}

// Student Comment: Getters and setters
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::incrementScoreBy(int points)
{
    score += points;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
// // Student Comment: Food management
// objPos GameMechs::getFood() const
// {
//     return food;
// }

// int GameMechs::getFoodEaten() const
// {
//     return foodEaten;
// }

// int GameMechs::getSpecialFoodIndex1() const
// {
//     return specialFoodIndex1;
// }

// int GameMechs::getSpecialFoodIndex2() const
// {
//     return specialFoodIndex2;
// }

// void GameMechs::incrementFoodEaten()
// {
//     foodEaten++;
// }

// // Student Comment: Generates a new food item ensuring no overlap with snake body or other food items
// void GameMechs::generateFood(const objPosArrayList& snakeBody)
// {
//     bool validPosition = false;
//     int x, y;

//     while (!validPosition)
//     {
//         x = 1 + rand() % (boardSizeX - 2);
//         y = 1 + rand() % (boardSizeY - 2);

//         validPosition = true;

//         // Student Comment: Check against snake body
//         for (int i = 0; i < snakeBody.getSize(); i++)
//         {
//             objPos snakeSegment = snakeBody.getElement(i);
//             if (snakeSegment.pos->x == x && snakeSegment.pos->y == y)
//             {
//                 validPosition = false;
//                 break;
//             }
//         }

//         // Student Comment: Check against existing food
//         for (int i = 0; i < foodBin.getSize(); i++) 
//         {
//             objPos existingFood = foodBin.getElement(i);
//             if (existingFood.pos->x == x && existingFood.pos->y == y) 
//             {
//                 validPosition = false;
//                 break;
//             }
//         }
//     }

//     food.setObjPos(x, y, '*');
// }

// // Student Comment: Initializes the food bin with multiple food items
// void GameMechs::initializeFoodBin(int numFoods)
// {
//     for (int i = 0; i < numFoods; i++)
//     {
//         int x = 1 + rand() % (boardSizeX - 2);
//         int y = 1 + rand() % (boardSizeY - 2);
//         char symbol = (i == specialFoodIndex1 || i == specialFoodIndex2) ? '$' : '*';
//         objPos food(x, y, symbol);
//         foodBin.insertTail(food);
//     }
// }

// // Student Comment: Returns a pointer to the food bin
// objPosArrayList* GameMechs::getFoodBin() const
// {
//     return const_cast<objPosArrayList*>(&foodBin);
// }

// // Student Comment: Regenerates a specific food item ensuring no overlap with the snake or other food items
// void GameMechs::regenerateFoodAt(int index, const objPosArrayList& snakeBody)
// {
//     if (index < 0 || index >= foodBin.getSize())
//     {
//         return;
//     }

//     bool validPosition = false;
//     int x, y;

//     while (!validPosition)
//     {
//         x = 1 + rand() % (boardSizeX - 2);
//         y = 1 + rand() % (boardSizeY - 2);

//         validPosition = true;

//         // Student Comment: Check against snake body
//         for (int i = 0; i < snakeBody.getSize(); i++)
//         {
//             objPos snakeSegment = snakeBody.getElement(i);
//             if (snakeSegment.pos->x == x && snakeSegment.pos->y == y)
//             {
//                 validPosition = false;
//                 break;
//             }
//         }

//         // Student Comment: Check against other food items
//         if (validPosition)
//         {
//             for (int i = 0; i < foodBin.getSize(); i++)
//             {
//                 if (i == index) continue;
//                 objPos existingFood = foodBin.getElement(i);
//                 if (existingFood.pos->x == x && existingFood.pos->y == y)
//                 {
//                     validPosition = false;
//                     break;
//                 }
//             }
//         }
//     }

//     char symbol = '*';
//     if (index == specialFoodIndex1 || index == specialFoodIndex2)
//     {
//         symbol = '$';
//     }

//     objPos newFood(x, y, symbol);

//     foodBin.setElement(index, newFood);
// }

// // Student Comment: Applies effects of special food and regenerates it
// void GameMechs::applySpecialFoodEffect(int index, Player* player)
// {
//     if (index == specialFoodIndex1)
//     {
//         incrementScoreBy(10);
//     }
//     else if (index == specialFoodIndex2)
//     {
//         incrementScoreBy(50);
//         player->growBy(10);
//     }

//     regenerateFoodAt(index, *player->getPlayerPosList());
// }

// // Student Comment: Regenerates all food items
// void GameMechs::regenerateAllFood(const objPosArrayList& snakeBody)
// {
//     for (int i = 0; i < foodBin.getSize(); i++)
//     {
//         regenerateFoodAt(i, snakeBody);
//     }
// }

// // Student Comment: Regenerates only the special food items
// void GameMechs::regenerateSpecialFoods(const objPosArrayList& snakeBody)
// {
//     regenerateFoodAt(specialFoodIndex1, snakeBody);
//     regenerateFoodAt(specialFoodIndex2, snakeBody);
// }