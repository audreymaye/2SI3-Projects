#include "Player.h"
#include "MacUILib.h"

//constructor
Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    gameFood = thisFood;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*');
    playerPosList = new objPosArrayList();

    playerPosList->insertHead(tempPos);
    
}

//destructor
Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
   return playerPosList;
}

void Player::updatePlayerDir()
{

  //change direction state based on user input
  switch(mainGameMechsRef->getInput()) {
    case 'w':
                if(myDir!=DOWN) {
                    myDir = UP;
                }
                break;

            case 's':
                if(myDir!=UP) {
                    myDir = DOWN;
                }
                break;

            case 'a':
                if(myDir!=RIGHT) {
                    myDir = LEFT;
                }
                break;

            case 'd':
                if(myDir!=LEFT) {
                    myDir = RIGHT;
                }
                break;
            default:
                break;
  }      
}

void Player::movePlayer()
{

objPos currentHead;
playerPosList->getHeadElement(currentHead);

//calculate new head coordinate
switch(myDir) {
    case LEFT:
        if(currentHead.x == 1) {
            currentHead.x = mainGameMechsRef->getBoardSizeX()-1;
        }
        currentHead.x --;
        break;

    case RIGHT:
        if(currentHead.x == mainGameMechsRef->getBoardSizeX()-2) {
            currentHead.x = 0;
        }
        currentHead.x ++;
        break;

    case UP:
        if(currentHead.y == 1) {
            currentHead.y = mainGameMechsRef->getBoardSizeY()-1;
        }
        currentHead.y --;
        break;

    case DOWN:
        if(currentHead.y == mainGameMechsRef->getBoardSizeY()-2) {
            currentHead.y = 0;
        }
        currentHead.y ++;
        break;
    default:
        break;
}   
    //if snake eats itself set lostflag and exit flag
    if (checkSelfCollision(currentHead))
    {
        mainGameMechsRef->setLostFlag();
        mainGameMechsRef->setExitTrue();
        return;
    }
    playerPosList->insertHead(currentHead);

    //check if snake ate food
    if (checkFoodConsumption(currentHead) == false)
    {
        playerPosList->removeTail();
    }
    else
    {
        increasePlayerLength();
    }
      
}

//check if snake head and food pos is equal
 bool Player::checkFoodConsumption(objPos &currentHead)
 {
    objPos tempFood;

    playerPosList->getHeadElement(currentHead);
    gameFood->getFoodPos(tempFood);

    return currentHead.isPosEqual(&tempFood);
 }

//increase snake body
 void Player::increasePlayerLength()
 {
    gameFood->generateFood(playerPosList);
    mainGameMechsRef->incrementScore();
 }

//check if snake head is equal to any of the snake body parts
 bool Player::checkSelfCollision(objPos &currentHead)
 {
    objPos playerBody;
    for (int b = 1; b < playerPosList->getSize(); b++)
    {   
        playerPosList->getElement(playerBody, b);
        if (playerBody.isPosEqual(&currentHead))
        {
            return true;
        }
        
    }
    return false;
 }

