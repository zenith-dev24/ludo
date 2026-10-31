#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "boardmath.hpp"

using namespace std;

class LudoGame{
    private:
        vector<Ludo::player> players;
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
            switch(abspos){
                case 0:
                case 8:
                case 13:
                case 21:
                case 26:
                case 34:
                case 39:
                case 47:
                    return true;
                default:
                    return false;
            }
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
                    if(token.state == TokenState::MAIN_PATH){
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
            Ludo::player& current = players[currentplayerIndex];
            cout << "\n" << current.color << "'s Turn <<<\n";
            int dice = rollDice();
            cout << "Rolled a" << dice << '\n';
            bool tokenMoved = false;
            for(auto& t : current.tokens){
                if(t.state == TokenState::BASE && dice == 6){
                    cout << "Unlocking Token" << t.id << "from base" << '\n';
                    t.state = TokenState::MAIN_PATH;
                    t.stepsTaken = 0;
                    tokenMoved = true;
                    break;
                }
                else if(t.state == TokenState::MAIN_PATH){
                    t.stepsTaken += dice;
                    int abspos = getAbsolutePosition(current.startPosition,t.stepsTaken);
                    if(t.stepsTaken > 50){
                        t.state = TokenState::HOME_PATH;
                        cout << "Moved Token" << t.id << "into the home path" << '\n';
                    }
                    else{
                        cout << "Moved Token" << t.id << "on main path to absolute square" << abspos << '\n';
                        handleCapture(abspos,current.color);
                    }
                    tokenMoved = true;
                    break;
                }
                else if(t.state == TokenState::HOME_PATH){
                    if(t.stepsTaken + dice <= 57){
                        t.stepsTaken += dice;
                        t.state = TokenState::FINISHED;
                        cout << "Token" << t.id << "REACHED THE CENTER!" << '\n';
                    }
                        else{
                            cout << "Moved Token" << t.id << "closer to center" << (57 - t.stepsTaken) << "steps left" << '\n';
                        }
                        tokenMoved = true;
                        break;
                    }
                }
                if(!tokenMoved){
                    cout << "No valid moves available!" << '\n';
                }
                if(dice != 6){
                    currentplayerIndex = (currentplayerIndex + 1) % players.size();
                }
                else{
                    cout << "Rolled a 6! You got another turn!" << '\n';
                }
        }
};
int main(){
    int numplayers = 0;
    while(numplayers < 2 || numplayers > 4){
        cout << "Enter the number of players (2-4):";
        cin >> numplayers;
    }
    LudoGame game(numplayers);
    char input;

    cout << "Game started! Type 'r' and press Enter to roll the dice, or 'q' to quit." << '\n';
    while(!game.isGameOver()){
        game.printBoard();
        cout << ">";
        cin >> input;
        if(input == 'q'){
            cout << "Quitting the game." << '\n';
            break;
        }
        else if(input == 'r'){
            game.playTurn();
        }
        else{
            cout << "Invalid input!" << '\n';
        }
    }
    return 0;
}
