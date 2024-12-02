#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DEFAULT_DELAY 25000
#define SPEED_BOOST_DELAY 100
#define TOTAL_FOOD 5

// Student Comment: Global game state variables
bool exitFlag;
Player* myPlayer; // Student Comment: Player object representing the snake
GameMechs* myGM; // Student Comment: Game mechanics object holding the game state
Food* myFood;

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

    // Student Comment: Initialize game state
    Initialize();

    // Student Comment: Main game loop: Runs while the game is not over or exited
    while(!myGM->getExitFlagStatus() && !myGM->getLoseFlagStatus())
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    // Student Comment: Cleanup game resources after the game loop ends
    CleanUp();

}

// Student Comment: Initializes the game state
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Student Comment: Instantiate game mechanics and player objects
    myGM = new GameMechs();
    myPlayer = new Player(myGM);
    myFood = new Food(myGM, myPlayer, TOTAL_FOOD);
}

// Student Comment: Processes user input for controlling the snake
void GetInput(void)
{
    if(MacUILib_hasChar()) // Student Comment: Check if there is a character input
    {
        char input = MacUILib_getChar(); // Student Comment: Get the input character
        if (input == 27) // Student Comment: Escape key to exit
        {
            myGM->setExitTrue();
        }
        else
        {
            myGM->setInput(input); // Student Comment: Set input for further processing
        }
    }
}

// Student Comment: Updates the game state based on user input and game logic
void RunLogic(void)
{
    myPlayer->updatePlayerDir(); // Student Comment: Update player (snake) direction based on input

    objPos playerPos = myPlayer->getPlayerPos(); // Student Comment: Get current player position
    objPosArrayList* foodBin = myFood->getFoodBin(); // Student Comment: Get the food bin (list of food items)

    bool foodConsumed = false; // Student Comment: Flag to track if any food was consumed
    int consumedFoodIndex = -1; // Student Comment: To track which food was consumed

    // Student Comment: Check if the player has eaten any food
    for (int i = 0; i < foodBin->getSize(); i++)
    {
        objPos food = foodBin->getElement(i);

        // Student Comment: Check if player head overlaps with food
        if (playerPos.isPosEqual(&food))
        {
            foodConsumed = true;
            consumedFoodIndex = i; // Student Comment: Track the consumed food index

            // Student Comment: Check if the food is special
            if (food.getSymbol() == '$')
            {
                myFood->applySpecialFoodEffect(i, myPlayer); // Student Comment: Apply special food effect // Jethro --- myGM

                // Student Comment: Apply speed boost if the food is special food
                if (i == myFood->getSpecialFoodIndex1())
                {
                    speedBoostTimer = 200;
                    currentDelay = SPEED_BOOST_DELAY;

                    // Student Comment: Regenerate all food locations
                    // myFood->regenerateAllFood(*myPlayer->getPlayerPosList()); // Jethro -------------------------------- myGM
                }
                // else if (i == myFood->getSpecialFoodIndex2())
                // {
                //     // myFood->regenerateSpecialFoods(*myPlayer->getPlayerPosList()); // Student Comment: Regenerate only special foods after consumption
                // } // Jethro -------------------------------------------------------------------------------------------- myGM
            }
            else
            {
                // Student Comment: Regular food: grow player and update score
                myPlayer->growPlayer();
                myGM->incrementScore();

                // Student Comment: Regenerate consumed food in a new position
                myFood->regenerateFoodAt(i, *myPlayer->getPlayerPosList()); // Jethro----------------------------------- myGM
            }

            myFood->incrementFoodEaten(); // Student Comment: Increment food eaten counter // Jethro-------------------- myGM
            break;
        }
    }
    myPlayer->movePlayer(); // Student Comment: Move the player after food consumption check

    // Student Comment: Check for collision with the snake's body (self-collision)
    objPosArrayList* snakeBody = myPlayer->getPlayerPosList();
    objPos head = snakeBody->getHeadElement(); // Student Comment: Get the head of the snake

    // Student Comment: Check if the head collides with any part of the body
    for (int i = 1; i < snakeBody->getSize(); i++)
    {
        objPos bodyPart = snakeBody->getElement(i);
        if (head.isPosEqual(&bodyPart))
        {
            myGM->setLoseFlag(); // Student Comment: Set lose flag if collision occurs
            break;
        }
    }
}

// Student Comment: Draws the current game state on the screen
void DrawScreen(void)
{
    MacUILib_clearScreen();

    // objPos playerPos = myPlayer->getPlayerPos(); <- Original code
    // Student Comment: Get food bin and snake body for rendering
    objPosArrayList* foodBin = myFood->getFoodBin();
    objPosArrayList* snakeBody = myPlayer->getPlayerPosList();

    // Student Comment: Loop through each row and column to draw the game board
    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            bool isBodyPart = false; // Student Comment: Flag to check if the current cell is part of the snake

            // objPosArrayList* snakeBody = myPlayer->getPlayerPosList();
            // Student Comment: Check if the current cell is occupied by a snake body part
            for (int k = 0; k < snakeBody->getSize(); k++)
            {
                objPos bodyPart = snakeBody->getElement(k);
                if (bodyPart.pos->y == i && bodyPart.pos->x == j)
                {
                    isBodyPart = true; // Student Comment: Cell is part of the snake's body
                    
                    // Student Comment: Draw head '@' and body '0'
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
                bool isFood = false; // Student Comment: Flag to check if the current cell is food

                // Student Comment: Check if the current cell contains food
                for (int f = 0; f < foodBin->getSize(); f++)
                {
                    objPos food = foodBin->getElement(f);
                    if (food.pos->y == i && food.pos->x == j)
                    {
                        isFood = true;
                        MacUILib_printf("%c", food.getSymbol()); // Student Comment: Draw food
                        break;
                    }
                }

                if (!isFood)
                {
                    // Student Comment: Draw the border or empty space
                    if (i == 0 || j == 0 || i == myGM->getBoardSizeY() - 1 || j == myGM->getBoardSizeX() - 1)
                    {
                        MacUILib_printf("#"); // Student Comment: Draw border
                    }
                    else
                    {
                        MacUILib_printf(" "); // Student Comment: Draw empty space
                    }
                }
            }
        }
        MacUILib_printf("\n"); // Student Comment: Newline after each row
    }

    // Student Comment: Display score and food eaten on the screen
    MacUILib_printf("Eat food [*] to grow the snake and increase your score!\nSpecial food [$] can either:\n\t1. Increase speed temporarily and gain 10 points\n\t2. Grow the snake by 10 and score by 50\n");
    MacUILib_printf("Score: %d\t", myGM->getScore());
    MacUILib_printf("Food Eaten: %d\n", myFood->getFoodEaten());

    // Student Comment: Display game controls
    MacUILib_printf("Controls: \n[W]\tUp\n[A]\tLeft\n[S]\tDown\n[D]\tRight\n[Esc]\tQuit\n");

    // for (int i = 0; i < TOTAL_FOOD; i++){
    //     printf("%d %d %c", foodBin->getElement(i).getObjPos().pos->x, foodBin->getElement(i).getObjPos().pos->y, foodBin->getElement(i).getSymbol());
    // }
}

// Student Comment: Controls the delay for the game loop
void LoopDelay(void)
{
    // MacUILib_Delay(DELAY_CONST); // 0.1s delay
    // Student Comment: Handle speed boost timer and reset delay
    if (speedBoostTimer > 0)
    {
        speedBoostTimer--;
        if (speedBoostTimer == 0)
        {
            currentDelay = DEFAULT_DELAY; // Student Comment: Reset to default delay after boost ends
        }
    }

    MacUILib_Delay(currentDelay); // Student Comment: Delay for the next loop iteration
}

// Student Comment: Cleans up resources and displays game over message
void CleanUp(void)
{

    MacUILib_clearScreen();

    // Student Comment: Display game over message based on the exit condition
    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\nGame Over: You died.\n");
        MacUILib_printf("\nFinal Score: %d\n", myGM->getScore());
        MacUILib_printf("Food Eaten: %d\n", myFood->getFoodEaten());
    }
    else if (myGM->getExitFlagStatus())
    {
        MacUILib_printf("\nGame Over: Force quit.\n");
    }

    // Student Comment: Clean up dynamically allocated objects
    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}