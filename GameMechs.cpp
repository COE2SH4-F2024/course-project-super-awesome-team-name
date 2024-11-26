#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    // GameMechs();
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // no pointers/heap data members
    
    // Student Comment: The destructor is empty because the class
    // has no dynamic memory management, meaning the destructor could be safely removed.
}

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
objPos GameMechs::getFood() const
{
    return food;
}

void GameMechs::generateFood(const objPosArrayList& snakeBody)
{
    srand(time(0));
    bool validPosition = false;
    int x, y;

    while (!validPosition)
    {
        x = 1 + rand() % (boardSizeX - 2);
        y = 1 + rand() % (boardSizeY - 2);

        validPosition = true;
        for (int i = 0; i < snakeBody.getSize(); i++)
        {
            objPos snakeSegment = snakeBody.getElement(i);
            if (snakeSegment.pos->x == x && snakeSegment.pos->y == y)
            {
                validPosition = false;
                break;
            }
        }
    }

    food.setObjPos(x, y, '*');
}