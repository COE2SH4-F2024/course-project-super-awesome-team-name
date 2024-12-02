#include "Player.h"

// Student Comment: Constructor initializes the snake at the start position and links to game mechanics
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    // Student Comment: Initialize snake's position at the center of the board with head symbol '@'
    playerPosList = new objPosArrayList();
    objPos initialPosition(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');
    playerPosList->insertHead(initialPosition);
}

// Student Comment: Destructor cleans up dynamically allocated memory for player position list
Player::~Player()
{
    delete playerPosList;
}

// Student Comment: Returns the current head position of the snake
objPos Player::getPlayerPos() const
{
    return playerPosList->getHeadElement();
}

// Student Comment: Returns the list of snake body segments
objPosArrayList* Player::getPlayerPosList() const
{
    return playerPosList;
}

// Student Comment: Updates the direction of the snake based on user input
void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    // Student Comment: Get the input from the GameMechs class
    char input = mainGameMechsRef->getInput();    
    if(input != 0)  // if not null character
    {
        // Student Comment: Change the direction based on input, but prevent reverse movement
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
                break; // Student Comment: Ignore other inputs
        }
        mainGameMechsRef->clearInput(); // Student Comment: Clear the input buffer  
    }
}

// Student Comment: Moves the player (snake) in the current direction
void Player::movePlayer()
{
    // Student Comment: Get the current position of the snake's head
    objPos headPos = playerPosList->getHeadElement();
    int newX = headPos.pos->x;
    int newY = headPos.pos->y;

    // PPA3 Finite State Machine logic
    // Student Comment: Update the head's position based on the current direction
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
        case STOP: // Student Comment: Do nothing if direction is STOP
        default:
            return;
    }

    // Student Comment: Create a new head position and update the player body
    objPos newHead(newX, newY, '@');
    playerPosList->insertHead(newHead); // Student Comment: Insert new head at the front
    playerPosList->removeTail(); // Student Comment: Remove the tail (to simulate movement)
}

// More methods to be added
// Student Comment: Adds a new segment to the snake at the current head position
void Player::growPlayer()
{
    // Student Comment: Get current head position and calculate new position for the body segment
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

    // Student Comment: Insert a new body segment at the front of the snake
    objPos newHead(newX, newY, '@');
    playerPosList->insertHead(newHead);

}

// Student Comment: Grows the snake by a specified number of segments
void Player::growBy(int length)
{
    // Student Comment: Add multiple segments to the snake body
    for (int i = 0; i < length; i++)
    {
        objPos tail = playerPosList->getTailElement(); // Student Comment: Get the last segment of the snake
        objPos newSegment(tail.pos->x, tail.pos->y, '0'); // Student Comment: Represent body segments with '0'
        playerPosList->insertTail(newSegment); // Student Comment: Add the new segment at the tail
    }
}