#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '*';
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();    
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            // case ' ':  // exit
            //     exitFlag = 1;
            //     break;

            // Add more key processing here
            case 'w':
            case 'W':
                if (myDir != DOWN)
                {
                    myDir = UP;
                }
                break;
            // Add more key processing here
            case 'a':
            case 'A':
                if (myDir != RIGHT)
                {
                    myDir = LEFT;
                }
                break;
            // Add more key processing here   
            case 's':
            case 'S':
                if (myDir != UP)
                {
                    myDir = DOWN;
                }
                break;
            case 'd':
            case 'D':
                if (myDir != LEFT)
                {
                    myDir = RIGHT;
                }
                break;

            // case '.':
            //     if (speed < 5)
            //     {
            //         speed ++;
            //     }
            //     break;
            // case ',':
            //     if (speed > 1)
            //     {
            //         speed --;
            //     }
            default:
                // myDir = 5; REMOVE WHEN DONE
                break;
        }
        // storage = input; // REMOVE AFTER DONE !!!
        mainGameMechsRef->clearInput();      
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
        case UP: // cannot be DOWN
            playerPos.pos->y = (playerPos.pos->y - 1) > 0? playerPos.pos->y - 1 : mainGameMechsRef->getBoardSizeY() - 2; // to account for border, decrease index range
            break;
        case LEFT: // cannot be RIGHT
            playerPos.pos->x = (playerPos.pos->x - 1) > 0? playerPos.pos->x - 1 : mainGameMechsRef->getBoardSizeX() - 2;
            break;
        case DOWN: // cannot be UP
            playerPos.pos->y = (playerPos.pos->y + 1) < mainGameMechsRef->getBoardSizeY() - 1? playerPos.pos->y + 1 : 1;
            break;
        case RIGHT: // cannot be LEFT
            playerPos.pos->x = (playerPos.pos->x + 1) < mainGameMechsRef->getBoardSizeX() - 1? playerPos.pos->x + 1 : 1;
            break;
        case STOP:
        default:
            break;
    }

    // if (myDir != STOP){
    //     move_Count++;
    // }
}

// More methods to be added