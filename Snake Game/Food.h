#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <ctime>

#include "GameMechs.h"
#include "objPos.h"
#include "Player.h"

using namespace std;


class Food 
{
    private:
        objPos foodPos; //food object 

        GameMechs* mainGameMechsRef; //GameMech reference

    public:
    Food(GameMechs* thisGMRef); // constructor

    void generateFood(objPosArrayList* blockOff); 
    void getFoodPos(objPos &returnPos);
   


};
#endif