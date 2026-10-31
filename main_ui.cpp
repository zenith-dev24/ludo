#include <raylib.h>
#include <iostream>

using namespace std;
using namespace Ludo;

Vector2 mainPath[52] = {
{450f,100f},
{450f,150f},
{450f,200f},
{450f,250f},
{450f,300f},
{500f,350f},
{550f,350f},
{600f,350f},
{650f,350f},
{700f,350f},
{750f,350f},
{750f,400f},
{750f,450f},
{700f,450f},
{650f,450f},
{600f,450f},
{550f,450f},
{500f,450f},
{450f,500f},
{450f,550f},
{450f,600f},
{450f,650f},
{450f,700f},
{450f,750f},
{400f,750f},
{350f,750f},
{350f,700f},
{350f,650f},
{350f,600f},
{350f,550f},
{350f,500f},
{300f,450f},
{250f,450f},
{200f,450f},
{150f,450f},
{100f,450f},
{50f,450f},
{50f,450f},
{50f,350f},
{100f,350f},
{150f,350f},
{200f,350f},
{250f,350f},
{300f,350f},
{350f,300f},
{350f,250f},
{350f,200f},
{350f,150f},
{350f,100f},
{350f,50f},
{400f,50f},
{450f,50f},
};
Vector2 redHome[5] = {{0.0f,0.0f}};
Vector2 greenHome[5] = {{0.0f,0.0f}};
Vector2 yellowHome[5] = {{0.0f,0.0f}};
Vector2 blueHome[5] = {{0.0f,0.0f}};

Vector2 redBase[4] = {{150,150},{200,150},{150,200},{200,200}};
Vector2 greenBase[4] = {{600,150},{650,150},{600,200},{650,200}};
Vector2 yellowBase[4] = {{600,600},{650,600},{600,650},{650,650}};
Vector2 blueBase[4] = {{150,600},{200,600},{150,650},{200,650}};

Color getRaylibColor(string colorName){
   if(colorName == "RED"){
      return RED;
   }
   if(colorName == "GREEN"){
      return GREEN;
   }
   if(colorName == "YELLOW"){
      return YELLOW;
   }
   if(colorName == "BLUE"){
      return BLUE;
   }
   else{
      return BLACK;
   }
}
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
}