#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "boardmath.hpp"
#include "ludo.hpp"

using namespace std;
using namespace Ludo;

LudoGame :: LudoGame(int numPlayers){
    currentplayerIndex = 0;
    currentRoll = 0;
    needsToRoll = true;
    gameOver = false;
    if(numPlayers >= 2){
        players.push_back(Ludo::player("RED",0));
        players.push_back(Ludo::player("YELLOW",26));
    }
    if(numPlayers >= 3){
        players.push_back(Ludo::player("GREEN",13));
    }
    if(numPlayers == 4){
        players.push_back(Ludo::player("BLUE",39));
    }
}
void LudoGame :: rollDice(){
            static random_device rd;
            static mt19937 gen(rd());
            uniform_int_distribution<> dis(1,6);
            currentRoll = dis(gen);
            needsToRoll = false;
        }
int LudoGame :: getAbsolutePosition(int startPostion,int stepsTaken){
            return (startPostion + stepsTaken) % 52;
        }
bool LudoGame :: isSafeSquare(int abspos){
    for(int safe : Safe_Tiles){
        if(abspos == safe){
            return true;
        }
    }
    return false;
}
void LudoGame :: handleCapture(int targetabspos,string movingcolor){
            if(isSafeSquare(targetabspos)){
                return;
            }
            for(auto& player : players){
                if(player.color == movingcolor){
                    continue;
                }
                for(auto& token : player.tokens){
                    if(token.state == TokenState::MAIN_PATH){
                        int tokenabspos = getAbsolutePosition(player.startPosition,token.stepsTaken);
                        if(tokenabspos == targetabspos){
                            token.state = TokenState::BASE;
                            token.stepsTaken = 0;
                        }
                    }
                }
            }
        }
bool LudoGame :: isGameOver(){
    for(const auto& p : players){
        if(p.hasWon()){
            gameOver = true;
            return true;
        }
    }
    return false;
}
bool LudoGame :: tryMoveToken(int tokenId){
    Ludo::player& current = players[currentplayerIndex];
    Ludo::Token& t = current.tokens[tokenId];
    bool moveSuccesful = false;
    if(t.state == TokenState :: BASE){
        if(currentRoll == 6){
            t.state = TokenState::MAIN_PATH;
            t.stepsTaken = 0;
            moveSuccesful = true;
        }
    }
    else if(t.state == TokenState::MAIN_PATH){
        if(t.stepsTaken + currentRoll > 50){
            t.state = TokenState::HOME_PATH;
        }
        t.stepsTaken += currentRoll;
        if(t.state == TokenState::MAIN_PATH){
            int abspos = getAbsolutePosition(current.startPosition,t.stepsTaken);
            handleCapture(abspos,current.color);
        }
        moveSuccesful = true;
    }
    else if(t.state == TokenState::HOME_PATH){
        if(t.stepsTaken + currentRoll <=57){
            t.stepsTaken += currentRoll;
            if(t.stepsTaken == 57){
                t.state = TokenState::FINISHED;
            }
            moveSuccesful = true;
        }
    }
    if(moveSuccesful){
        if(current.hasWon()){
            gameOver = true;
        }

        if(currentRoll != 6){
            currentplayerIndex = (currentplayerIndex + 1) % players.size();
        }
        needsToRoll = true;
        return true;
    }
    return false;
}
void LudoGame :: executeTurn(){
    for(int i = 0;i < 4;i++){
        if(tryMoveToken(i)){
            break;
        }
    }
}