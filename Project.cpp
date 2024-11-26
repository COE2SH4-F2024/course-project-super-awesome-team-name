#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

// USER ADDED COMMENT: make a global pointer to player and gamemech objects
Player* myPlayer;
GameMechs* myGM;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!myGM->getExitFlagStatus() && !myGM->getLoseFlagStatus())  // USER ADDED: while gamemech ->getEFStatus
    {
        // MacUILib_printf("Hello");
        GetInput();
        RunLogic();
        // MacUILib_printf("test bonjour");
        DrawScreen();
        // MacUILib_printf("HELLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLOOOOOOOOOOOOOOOOO");
        LoopDelay();
        // MacUILib_printf("HELLLLLLLLLLLLLLLOOOOOOOOOOOOO");
    }

    // MacUILib_printf("Hello");
    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // exitFlag = false;
    // initialize GM obj
    myGM = new GameMechs();
    // initialize player obj myPlayer = new Player(myGM)
    myPlayer = new Player(myGM);

    myGM->generateFood(*myPlayer->getPlayerPosList());
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
        // myGM->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();

    objPos playerPos = myPlayer->getPlayerPos();
    objPos foodPos = myGM->getFood();

    if (playerPos.isPosEqual(&foodPos))
    {
        myPlayer->growPlayer();
        myGM->incrementScore();
        myGM->generateFood(*myPlayer->getPlayerPosList());
    }
    else
    {
        myPlayer->movePlayer();
    }

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
    //int i = 0, j = 0, k = 0;
    //int item_Printed = 0;
    MacUILib_clearScreen();

    objPos playerPos = myPlayer->getPlayerPos();
    objPos foodPos = myGM->getFood();


    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            bool isBodyPart = false;

            objPosArrayList* snakeBody = myPlayer->getPlayerPosList();
            for (int k = 0; k < snakeBody->getSize(); k++)
            {
                objPos bodyPart = snakeBody->getElement(k);
                if (bodyPart.pos->y == i && bodyPart.pos->x == j)
                {
                    isBodyPart = true;
                    break;
                }
            }

            // item_Printed = 0; // find better implementation
            if (i == 0 || j == 0 || i == myGM->getBoardSizeY() - 1 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if (isBodyPart)
            {
                MacUILib_printf("%c", playerPos.getSymbol());
            }
            else if (foodPos.pos->y == i && foodPos.pos->x == j)
            {
                MacUILib_printf("%c", foodPos.getSymbol());
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    } 
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

    MacUILib_clearScreen();

    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\nGame Over: You died.\n");
    }
    else if (myGM->getExitFlagStatus())
    {
        MacUILib_printf("\nGame Over: Force quit.\n");
    }

    // USER ADDED: delete pointers
    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}