#ifndef BOARDMATH_HPP
#define BOARDMATH_HPP
#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace Ludo{
    constexpr int Total_Track_Tiles = 52;
    constexpr int Home_Path_Length = 5;
    constexpr int Finish_Step = Total_Track_Tiles + Home_Path_Length;

    const vector<int> Safe_Tiles = {0,8,13,21,26,34,39,47};

    enum class TokenState{
        BASE = 0,
        TRACK = 1,
        HOME_PATH = 2,
        FINISHED = 3
    };

    struct Token{
        int id;
        TokenState state;
        int stepsTaken;

        Token(int tokenId) : id(tokenId),state(TokenState::BASE),stepsTaken(0){}
    
        string toJson() const{
            ostringstream ss;
            ss << "{\"id\":" << id << ",\"state\":" << static_cast<int>(state) << ",\"stepsTaken\":" << stepsTaken << "}";
            return ss.str();
        }
    };
    
    class player{
        string color;
        vector<Token> tokens;
        int startPosition;
        player(string playerColor, int startPos){
            color = playerColor;
            startPosition = startPos;
            for(int i = 0;i < 4;i++){
                tokens.push_back(Token(i));
            }
        }

        bool hasWon() const{
            for(const auto& t : tokens){
                if(t.state != TokenState::FINISHED){
                    return false;
                }
            }
            return true;
        }
    }
};
#endif