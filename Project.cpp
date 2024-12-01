#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DEFAULT_DELAY 25000
#define SPEED_BOOST_DELAY 100

// Student Comment: Global game state variables
bool exitFlag;
Player* myPlayer; // Student Comment: Player object representing the snake
GameMechs* myGM; // Student Comment: Game mechanics object holding the game state

// Student Comment: Special food game speed boost effect
int currentDelay = DEFAULT_DELAY; // Student Comment: Delay for controlling game speed
int speedBoostTimer = 0; // Student Comment: Timer to track speed boost duration

// Student Comment: Function declarations
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while(!myGM->getExitFlagStatus() && !myGM->getLoseFlagStatus())
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    myGM->initializeFoodBin();
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
        if (input == 27)
        {
            myGM->setExitTrue();
        }
        else
        {
            myGM->setInput(input);
        }
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();

    objPos playerPos = myPlayer->getPlayerPos();
    objPosArrayList* foodBin = myGM->getFoodBin();

    bool foodConsumed = false; // Student Comment: Flag to track if any food was consumed
    int consumedFoodIndex = -1; // Student Comment: To track which food was consumed

    for (int i = 0; i < foodBin->getSize(); i++)
    {
        objPos food = foodBin->getElement(i);

        if (playerPos.isPosEqual(&food))
        {
            foodConsumed = true;
            consumedFoodIndex = i;

            if (food.getSymbol() == '$')
            {
                myGM->applySpecialFoodEffect(i, myPlayer);

                if (i == myGM->getSpecialFoodIndex1())
                {
                    speedBoostTimer = 200;
                    currentDelay = SPEED_BOOST_DELAY;

                    // Student Comment: Regenerate all food locations
                    myGM->regenerateAllFood(*myPlayer->getPlayerPosList());
                }
                else if (i == myGM->getSpecialFoodIndex2())
                {
                    myGM->regenerateSpecialFoods(*myPlayer->getPlayerPosList());
                }
            }
            else
            {
                myPlayer->growPlayer();
                myGM->incrementScore();

                myGM->regenerateFoodAt(i, *myPlayer->getPlayerPosList());
            }

            myGM->incrementFoodEaten();
            break;
        }
    }
    myPlayer->movePlayer();

    objPosArrayList* snakeBody = myPlayer->getPlayerPosList();
    objPos head = snakeBody->getHeadElement();

    for (int i = 1; i < snakeBody->getSize(); i++)
    {
        objPos bodyPart = snakeBody->getElement(i);
        if (head.isPosEqual(&bodyPart))
        {
            myGM->setLoseFlag();
            break;
        }
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // objPos playerPos = myPlayer->getPlayerPos(); <- Original code
    objPosArrayList* foodBin = myGM->getFoodBin();
    objPosArrayList* snakeBody = myPlayer->getPlayerPosList();

    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            bool isBodyPart = false;

            // objPosArrayList* snakeBody = myPlayer->getPlayerPosList();
            for (int k = 0; k < snakeBody->getSize(); k++)
            {
                objPos bodyPart = snakeBody->getElement(k);
                if (bodyPart.pos->y == i && bodyPart.pos->x == j)
                {
                    isBodyPart = true;
                    
                    if (k == 0)
                    {
                        MacUILib_printf("%c", '@');
                    }
                    else
                    {
                        MacUILib_printf("%c", '0');
                    }
                    break;
                }
            }

            if (!isBodyPart)
            {
                bool isFood = false;
                for (int f = 0; f < foodBin->getSize(); f++)
                {
                    objPos food = foodBin->getElement(f);
                    if (food.pos->y == i && food.pos->x == j)
                    {
                        isFood = true;
                        MacUILib_printf("%c", food.getSymbol());
                        break;
                    }
                }

                if (!isFood)
                {
                    if (i == 0 || j == 0 || i == myGM->getBoardSizeY() - 1 || j == myGM->getBoardSizeX() - 1)
                    {
                        MacUILib_printf("#");
                    }
                    else
                    {
                        MacUILib_printf(" ");
                    }
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\t", myGM->getScore());
    MacUILib_printf("Food Eaten: %d\n", myGM->getFoodEaten());
    MacUILib_printf("Controls: [W] Up [A] Left [S] Down [D] Right [Esc] Quit\n");
}

void LoopDelay(void)
{
    // MacUILib_Delay(DELAY_CONST); // 0.1s delay
    if (speedBoostTimer > 0)
    {
        speedBoostTimer--;
        if (speedBoostTimer == 0)
        {
            currentDelay = DEFAULT_DELAY;
        }
    }

    MacUILib_Delay(currentDelay);
}


void CleanUp(void)
{

    MacUILib_clearScreen();

    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\nGame Over: You died.\n");
        MacUILib_printf("\nFinal Score: %d\n", myGM->getScore());
        MacUILib_printf("Food Eaten: %d\n", myGM->getFoodEaten());
    }
    else if (myGM->getExitFlagStatus())
    {
        MacUILib_printf("\nGame Over: Force quit.\n");
    }

    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}