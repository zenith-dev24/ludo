#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "boardmath.hpp"

using namespace std;

class LudoGame{
    private:
        vector<player> players;
        int currentplayerIndex;
        int rollDice(){
            static random_device rd;
            static mt19937 gen(rd());
            uniform_int_distribution<> dis(1,6);
            return dis(gen);
        }
        int getAbsolutePosition(int startPostion,int stepsTaken){
            return (startPostion + stepsTaken) % 52;
        }
        bool isSafeSquare(int abspos){
            int safeSquares[] = {0,8,13,21,26,34,39,47};
            for(int s : safeSquares){
                if(abspos == s){
                    return true;
                }
            }
            return false;
        }
}
