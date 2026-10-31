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

     LudoGame game(4);

      while(!WindowShouldClose()){
         if(!game.gameOver){
            if(IsKeyPressed(KEY_SPACE)){
               if(game.needsToRoll){
                  game.rollDice();
               }
               else{
                  game.executeTurn();
               }
            }
         }
         BeginDrawing();
         ClearBackground(RAYWHITE);
         if(boardTexture.id != 0){
            DrawTexturePro(boardTexture,sourceRec,destRec,origin,0.0f,WHITE);
         }
         for(const auto& player : game.players){
            Color pColor = getRatlibColor(player.color);

            for(const auto& t : player.tokens){
               float drawX = 0,drawY = 0;
               if(t.state == TokenState::BASE){
                  if(player.color == "RED"){
                     drawX = redBase[t.id].x;drawY = redBase[t.id].y;
                  }
                  else if(player.color == "GREEN"){
                     drawX = greenBase[t.id].x;drawY = greenBase[t.id].y;
                  }
                  else if(player.color == "YELLOW"){
                     drawX = yellowBase[t.id].x;drawY = yellowBase[t.id].y;
                  }
                  else if(player.color == "BLUE"){
                     drawX = blueBase[t.id].x;drawY = blueBase[t.id].y;
                  }
               }
               else if(t.state == TokenState::MAIN_PATH){
                  int absPos = game.getAbsolutePosition(player.startPosition,t.stepsTaken);
                  drawX = mainPath[absPos].x;
                  drawY = mainPath[absPos].y;
               }
               else if{t.state == TokenState::HOME_PATH}{
                  int homeIdx = t.stepsTaken - 52;
                  if(homeIdx >= 0 && homeIdx < 5){
                     if(player.color == "RED"){
                     drawX = redBase[homeIdx].x;drawY = redBase[homeIdx].y;
                     }
                     else if(player.color == "GREEN"){
                        drawX = greenBase[homeIdx].x;drawY = greenBase[homeIdx].y;
                     }
                     else if(player.color == "YELLOW"){
                        drawX = yellowBase[homeIdx].x;drawY = yellowBase[homeIdx].y;
                     }
                     else if(player.color == "BLUE"){
                        drawX = blueBase[homeIdx].x;drawY = blueBase[homeIdx].y;
                     }
                  }
               }
               else if(t.state == TokenState::FINISHED){
                  drawX = 400;
                  drawY = 400;
               }
               if(drawX != 0 && drawY != 0){
                  DrawCircle(drawX,drawY,15,pColor);
                  DrawCircleLines(drawX,drawY,15,BLACK);
               }
            }
         }
         DrawRectangle(10,10,250,80,Fade(BLACK,0.7f));
         DrawText(TextFormat("Turn: %s",game.players[game.currentPlayerIndex].color.c_str()),20,20,20,getRaylibColor(game.players[game.currentPlayerIndex].color));
         if(game.needsToRoll){
            DrawRectangle(0,350,800,100,Fade(BLACK,0.8f));
            DrawText("GAME OVER!",280,380,40,GREEN);
         }
         EndDrawing();
     }
     UnloadTexture(boardTexture);
     CloseWindow();
     return 0;
}