#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArraylist.h"
#include "GameMechs.h"
#include "Food.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

//declare pointers to each class
GameMechs* myGM;
Food* myFood;
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    //run program if exit flag is not true
    while(myGM->getExitFlagStatus() == false)  
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

    //instantiate objects on the heap
    myGM = new GameMechs(36,18); 
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);

    //generate first food element
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myFood->generateFood(playerBody);
} 

void GetInput(void)
{

}

void RunLogic(void)
{
    //if user hits exit key (spacebar), set exit flag to true
    if (myGM->getInput() == ' ')
    {
        myGM->setExitTrue();
    }

    //based on user input, update and move player
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    //clear input so it won't be double processed
    myGM->clearInput();
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

    bool drawn;

    //declare a temporary food object to get generated food position
    objPos newfood;
    myFood->getFoodPos(newfood);

    //get player position list
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    
    for (int y = 0; y < myGM->getBoardSizeY(); y++)
    {
        for (int x = 0; x < myGM->getBoardSizeX(); x++)
        {
            drawn = false;

            //draw snake body
            for (int b = 0; b < playerBody->getSize(); b++)
            {
                playerBody->getElement(tempBody, b);
                if (tempBody.x == x && tempBody.y == y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            //if snake body is drawn skip the rest
            if (drawn) continue;
            //draw game boarder
            if (y == 0 || y == (myGM->getBoardSizeY()-1) || x == 0 || x == (myGM->getBoardSizeX()-1))
            {
                MacUILib_printf("#");
            }
            //draw food
            else if (y == newfood.y && x == newfood.x)
            {
                MacUILib_printf("%c", newfood.symbol);
            }
            
            else 
            {
                MacUILib_printf(" ");
            }

        }
        MacUILib_printf("\n");
    }
    //display score
    MacUILib_printf("Score: %d", myGM->getScore());
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //if lose flag is true, display game loss message
    if (myGM->getLoseFlagStatus())
    {
        MacUILib_clearScreen();
        MacUILib_printf("You died! Game Over\nYour score: %d", myGM->getScore());
    }
    //if player exits game, display regular game over message
    else
    {
        MacUILib_clearScreen();
        MacUILib_printf("Game Over\nYour score: %d", myGM->getScore());
    }
  
    MacUILib_uninit();

    //deallocate heap memory
    delete myGM;
    delete myFood;
    delete myPlayer;

}
