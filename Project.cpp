#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"

using namespace std;

#define DELAY_CONST 25000

bool exitFlag;
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
    MacUILib_clearScreen();

    // objPos playerPos = myPlayer->getPlayerPos(); <- Original code
    objPos foodPos = myGM->getFood();
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

            if (i == 0 || j == 0 || i == myGM->getBoardSizeY() - 1 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if (!isBodyPart && foodPos.pos->y == i && foodPos.pos->x == j)
            {
                MacUILib_printf("%c", foodPos.getSymbol());
            }
            else if (!isBodyPart)
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\t", myGM->getScore());
    MacUILib_printf("Food Eaten: %d\n", myGM->getScore());

    MacUILib_printf("Controls: ");
    MacUILib_printf("[W] Up    ");
    MacUILib_printf("[A] Left    ");
    MacUILib_printf("[S] Down    ");
    MacUILib_printf("[D] Right    ");
    MacUILib_printf("[Esc] Quit\n");
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

    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}