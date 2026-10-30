#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

const string RED =
const string GREEN =
const string BLUE =
const string YELLOW =

class Token{
    public :
        int id,x,y;
        bool isHome;
        int pathPostion;
        Token(int id,int startX,int startY):id(id),x(startX),(startY),isHome(true),pathPosition(-1){}
};
class Player