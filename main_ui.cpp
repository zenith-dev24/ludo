#include <raylib.h>
#include <iostream>

using namespace std;

int main(){
     const int screenWidth = 800;
     const int screenHeight = 800;

     InitWindow(screenWidth,screenHeight,"Ludo Game");
     SetTargetFPS(60);

     Texture2D boardTexture = LoadTexture("board.png");

     if(boardTexture.id == 0){
        cout << "ERROR: Failed to load board.png.Make sure the file exists." << "\n";
     }
     while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            if(boardTexture.id != 0){
               Rectangle sourceRec = { 0.0f,0.0f,(float)boardTexture.width,(float)boardTexture.height};
               Rectangle destRec = {0.0f,0.0f,(float)screenWidth,(float)screenHeight};
               Vector2 origin = {0.0f,0.0f};
               DrawTexturePro(boardTexture,sourceRec,destRec,origin,0.0f,WHITE);
            }
            else{
               DrawRectangle(100,100,600,600,LIGHTGRAY);
               DrawText("Missing board.png!",300,400,20,RED);
            }
            EndDrawing();
     }
     UnloadTexture(boardTexture);
     CloseWindow();
     return 0;
}k