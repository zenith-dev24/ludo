#ifndef LUDO_HPP
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
        bool needsToRoll;
        bool gameOver;
        bool hasValidMoves();

        LudoGame(int numPlayers);
        void rollDice();
        int getAbsolutePosition(int startPosition,int stepsTaken);
        bool isSafeSquare(int abspos);
        void handleCapture(int targetabspos,string movingcolor);
        bool isGameOver();
        bool tryMoveToken(int tokenId);
        void executeTurn();
};
#endif