#include <raylib.h>
#include <iostream>

using namespace std;

int main(){
     const int screenWidth = 800;
     const int screeHeight = 800;

     InitWindow(screenWidth,screenHeight,"Ludo Game");
     SetTargetFPS(60);

     Texture2D boardTexture = LoadTexture("board.png");

     if(boardTexture.id == 0){
        cout << "ERROR: Failed to load board.png.Make sure the file exists." << "\n";
     }
     while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(Raywhite);
            
     }
}