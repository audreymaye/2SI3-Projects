#include "GameMechs.h"
#include "MacUILib.h"

//constructor
GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 30;
    boardSizeX = 15;
    score = 0;

}

//special constructor
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;

}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar() != 0)
    {
        input = MacUILib_getChar();        
    } 
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{  
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLostFlag()
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


