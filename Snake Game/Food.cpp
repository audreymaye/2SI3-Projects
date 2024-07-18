#include "Food.h"

//constructor
Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    srand(time(nullptr)); //seed the random generator
    foodPos.setObjPos(-1,-1,'o'); //initialize food object outside of gameboard
}

void Food::generateFood(objPosArrayList* blockOff)
{
    objPos tempBody;
    bool repeat;

    do
    {  
        //generate a random x,y coordinates
        repeat = false;
        foodPos.x = rand() % mainGameMechsRef->getBoardSizeX();
        foodPos.y = rand() % mainGameMechsRef->getBoardSizeY();
        //check if food x y overlap the game board
        if (foodPos.y == 0 || foodPos.y == (mainGameMechsRef->getBoardSizeY()-1) || foodPos.x == 0 || foodPos.x == (mainGameMechsRef->getBoardSizeX()-1))
        {
            repeat = true;
        }
        if (repeat) continue;
        //check if food x y overlap snake body
        for (int b=0; b < blockOff->getSize(); b++)
        {
            blockOff->getElement(tempBody, b);
            if (tempBody.isPosEqual(&foodPos))
            {
                repeat = true;
                break;
            }
            
        }
        
    } while (repeat);
    
}
 //return food object
void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}
