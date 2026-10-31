#indef LUDO_HPP
#define LUDO_HPP

#include <iostream>
#include <vector>
#include "boardmath.hpp"

using namespace std;
using namespace Ludo;

class LudoGame{
    public:
        vector<Ludo::player> players;
        int currentplayerIndex;
        int currentRoll;
        bool needstoRoll;
        bool gameOver;

        LudoGame(int numPlayers);
        void rollDice();
        int getAbsolutePosition(int startPosition,int stepsTaken);
        bool isSafeSquae(int abspos);
        void handleCapture(int targetabspos,string movingcolor);
        bool isGameOver();
        void playTurn();
};
#endif