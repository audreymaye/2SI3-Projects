#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Food;

class Player
{

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFood);
        ~Player();

        objPosArrayList* getPlayerPos(); //return PlayerPosList
        void updatePlayerDir();//update direction
        void movePlayer(); //move player coordinates
        bool checkFoodConsumption(objPos &currentHead); //check if snake ate food
        void increasePlayerLength(); //increase the snake body
        bool checkSelfCollision(objPos&currentHead); //check if snake ate body

    private:
        objPosArrayList* playerPosList;       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms, and Food Class
        GameMechs* mainGameMechsRef;
        Food* gameFood;
};

#endif