#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    /* playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '*'; */ // USCOM: initial code

    playerPosList = new objPosArrayList();
    objPos initialPosition(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');
    playerPosList->insertHead(initialPosition);
}


Player::~Player()
{
    delete playerPosList;
}

objPos Player::getPlayerPos() const
{
    return playerPosList->getHeadElement();
}

objPosArrayList* Player::getPlayerPosList() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();    
    if(input != 0)  // if not null character
    {
        switch(input)
        {
            case 'w':
            case 'W':
                if (myDir != DOWN)
                {
                    myDir = UP;
                }
                break;
            case 'a':
            case 'A':
                if (myDir != RIGHT)
                {
                    myDir = LEFT;
                }
                break;
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
            default:
                break;
        }
        mainGameMechsRef->clearInput();      
    }
}

void Player::movePlayer()
{
    objPos headPos = playerPosList->getHeadElement();
    int newX = headPos.pos->x;
    int newY = headPos.pos->y;
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
        case UP: // cannot be DOWN
            newY = (headPos.pos->y - 1) > 0 ? headPos.pos->y - 1 : mainGameMechsRef->getBoardSizeY() - 2; // to account for border, decrease index range
            break;
        case LEFT: // cannot be RIGHT
            newX = (headPos.pos->x - 1) > 0 ? headPos.pos->x - 1 : mainGameMechsRef->getBoardSizeX() - 2;
            break;
        case DOWN: // cannot be UP
            newY = (headPos.pos->y + 1) < mainGameMechsRef->getBoardSizeY() - 1 ? headPos.pos->y + 1 : 1;
            break;
        case RIGHT: // cannot be LEFT
            newX = (headPos.pos->x + 1) < mainGameMechsRef->getBoardSizeX() - 1 ? headPos.pos->x + 1 : 1;
            break;
        case STOP:
        default:
            return;
    }

    objPos newHead(newX, newY, '@');
    playerPosList->insertHead(newHead);
    playerPosList->removeTail();
}

// More methods to be added
void Player::growPlayer()
{
    objPos headPos = playerPosList->getHeadElement();
    int newX = headPos.pos->x;
    int newY = headPos.pos->y;

    switch (myDir)
    {
        case UP: // cannot be DOWN
            newY = (headPos.pos->y - 1) > 0 ? headPos.pos->y - 1 : mainGameMechsRef->getBoardSizeY() - 2; // to account for border, decrease index range
            break;
        case LEFT: // cannot be RIGHT
            newX = (headPos.pos->x - 1) > 0 ? headPos.pos->x - 1 : mainGameMechsRef->getBoardSizeX() - 2;
            break;
        case DOWN: // cannot be UP
            newY = (headPos.pos->y + 1) < mainGameMechsRef->getBoardSizeY() - 1 ? headPos.pos->y + 1 : 1;
            break;
        case RIGHT: // cannot be LEFT
            newX = (headPos.pos->x + 1) < mainGameMechsRef->getBoardSizeX() - 1 ? headPos.pos->x + 1 : 1;
            break;
        case STOP:
        default:
            return;
    }

    objPos newHead(newX, newY, '@');
    playerPosList->insertHead(newHead);

}

void Player::growBy(int length)
{
    for (int i = 0; i < length; i++)
    {
        objPos tail = playerPosList->getTailElement();
        objPos newSegment(tail.pos->x, tail.pos->y, '0');
        playerPosList->insertTail(newSegment);
    }
}