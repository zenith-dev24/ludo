#include <raylib.h>
#include <iostream>

using namespace std;

int main(){
     const int screenWidth = 800;
     const int screeHeight = 800;

     InitWindow(screenWidth,screenHeight,"Ludo Game");
     SetTargetFPS(60);

     Texture2D boardTexture = LoadTexture("board.png");
}