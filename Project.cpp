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

    while(myGM->getExitFlagStatus() == false || myGM->getLoseFlagStatus() == false)  // USER ADDED: while gamemech ->getEFStatus
    {
        // MacUILib_printf("Hello");
        GetInput();
        RunLogic();
        MacUILib_printf("test bonjour");
        DrawScreen();
        // MacUILib_printf("HELLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLOOOOOOOOOOOOOOOOO");
        LoopDelay();
        // MacUILib_printf("HELLLLLLLLLLLLLLLOOOOOOOOOOOOO");
    }
    MacUILib_printf("Hello");
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
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        myGM->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    int i = 0, j = 0, k = 0;
    int item_Printed = 0;
    MacUILib_clearScreen();
    for (i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (j = 0; j < myGM->getBoardSizeX(); j++)
        {
            objPos playerPos = myPlayer->getPlayerPos();
            // item_Printed = 0; // find better implementation
            if (i == 0 || j == 0 || i == myGM->getBoardSizeY() - 1 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if (playerPos.pos->y == i && playerPos.pos->x == j){
                MacUILib_printf("%c", playerPos.getSymbol()); // add a playerpos variable to avoid calling function multiple times
            }
            else{
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
    // USER ADDED: delete pointers
    delete myPlayer;
    delete myGM;

    MacUILib_clearScreen();    

    MacUILib_uninit();
}
