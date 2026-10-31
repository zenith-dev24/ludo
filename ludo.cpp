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
       
        void handleCapture(int targetabspos,string movingcolor){
            if(isSafeSquare(targetabspos)){
                return;
            }
            for(auto& player : players){
                if(player.color == movingcolor){
                    continue;
                }
                for(auto& token : player.tokens){
                    if(token.state == Tokenstate::MAIN_PATH){
                        int tokenabspos = getAbsolutePosition(player.startPosition,token.stepsTaken);
                        if(tokenabspos == targetabspos){
                            cout << ">>>" << player.color << " 's token was captured and sent back to BASE!" << endl;
                            token.state = TokenState::BASE;
                            token.stepsTaken = 0;
                        }
                    }
                }
            }
        }
    public:
        LudoGame(int numPlayers){
            currentplayerIndex = 0;
            if(numPlayers >= 2){
                players.push_back(player("RED",0));
                players.push_back(player("YELLOW",26));
                players.push_back(player("GREEN",13));
                players.push_back(player("BLUE",39));
            }
        }
        bool isGameOver(){
            for(const auto& p : players){
                if(p.hasWon()){
                    cout << "\n*** " << p.color << "WINS THE GAME! ***\n";
                    return true;
                }
            }
            return false;
        }
        void printBoard(){
            cout << "\n-- Current Board State --\n";
            for(const auto& p : players){
                cout << p.color << ": [";
                for(const auto& t : p.tokens){
                    if(t.state == TokenState::BASE){
                        cout << "B";
                    }
                    else if(t.state == TokenState::FINISHED){
                        cout << "F";
                    }
                    else{
                        cout << t.stepsTaken << " ";
                    }
                }
                cout << "]\n";
            }
            cout << "--------------------------\n";
        }
        void playTurn(){
            player& current = players[currentplayerindex];
            cout << "\n" << current.color << "'s Turn <<<\n";
            int dice = rollDice();
            cout << "Rolled a" << dice << endl;
            bool tokenMoved = false;
            for(auto& t : current.tokens){
                if(t.state == TokenState::BASE && dice == 6){
                    cout << "Unlocking Token" << t.id << "from base" << endl;
                    t.state = TokenState::MAIN_PATH;
                    t.stepsTaken = 0;
                    tokenMoved = true;
                    break;
                }
            }
        }
};
int main(){
    int numplayers;
    while(numplayers < 2 || numplayers > 4){
        cout << "Enter the number of players (2-4):";
        cin >> numplayers;
    }
    return0;
}
