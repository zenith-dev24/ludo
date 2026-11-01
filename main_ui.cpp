#include <raylib.h>
#include <iostream>
#include "ludo.hpp"

using namespace std;
using namespace Ludo;

Vector2 mainPath[52] = {
{450.0f,100.0f},
{450.0f,150.0f},
{450.0f,200.0f},
{450.0f,250.0f},
{450.0f,300.0f},
{500.0f,350.0f},
{550.0f,350.0f},
{600.0f,350.0f},
{650.0f,350.0f},
{700.0f,350.0f},
{750.0f,350.0f},
{750.0f,400.0f},
{750.0f,45.00f},
{700.0f,450.0f},
{650.0f,450.0f},
{600.0f,450.0f},
{550.0f,450.0f},
{500.0f,450.0f},
{450.0f,500.0f},
{450.0f,550.0f},
{450.0f,600.0f},
{450.0f,650.0f},
{450.0f,700.0f},
{450.0f,750.0f},
{400.0f,750.0f},
{350.0f,750.0f},
{350.0f,700.0f},
{350.0f,650.0f},
{350.0f,600.0f},
{350.0f,550.0f},
{350.0f,500.0f},
{300.0f,450.0f},
{250.0f,450.0f},
{200.0f,450.0f},
{150.0f,450.0f},
{100.0f,450.0f},
{50.0f,450.0f},
{50.0f,450.0f},
{50.0f,350.0f},
{100.0f,350.0f},
{150.0f,350.0f},
{200.0f,350.0f},
{250.0f,350.0f},
{300.0f,350.0f},
{350.0f,300.0f},
{350.0f,250.0f},
{350.0f,200.0f},
{350.0f,150.0f},
{350.0f,100.0f},
{350.0f,50.0f},
{400.0f,50.0f},
{450.0f,50.0f},
};
Vector2 redHome[5] = {{0.0f,0.0f}};
Vector2 greenHome[5] = {{0.0f,0.0f}};
Vector2 yellowHome[5] = {{0.0f,0.0f}};
Vector2 blueHome[5] = {{0.0f,0.0f}};

Vector2 greenBase[4] = {{150,150},{200,150},{150,200},{200,200}};
Vector2 redBase[4] = {{600,150},{650,150},{600,200},{650,200}};
Vector2 blueBase[4] = {{600,600},{650,600},{600,650},{650,650}};
Vector2 yellowBase[4] = {{150,600},{200,600},{150,650},{200,650}};

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
Vector2 getTokenDrawPosition(LudoGame& game,int playerIdx,int tokenIdx){
   const Ludo::player& player = game.players[playerIdx];
   const Ludo::Token& t = player.tokens[tokenIdx];

   if(t.state == TokenState::BASE){
      if(player.color == "RED"){
         return redBase[t.id];
      }
      if(player.color == "GREEN"){
         return greenBase[t.id];
      }
      if(player.color == "YELLOW"){
         return yellowBase[t.id];
      }
      if(player.color == "BLUE"){
         return blueBase[t.id];
      }
   }
   else if(t.state == TokenState::MAIN_PATH){
      int abdPos = game.getAbsolutePostion(player.startPosition,t.stepsTaken);
      return mainPath[absPos];
   }
   else if(t.state == TokenState::HOME_PATH){
      int homeIdx = t.stepsTaken - 52;
      
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
            Rectangle sourceRec = {0.0f,0.0f,(float)boardTexture.width,(float)boardTexture.height};
            Rectangle destRec = {0.0f,0.0f,(float)screenWidth,(float)screenHeight};
            Vector2 origin = {0.0f,0.0f};
            DrawTexturePro(boardTexture,sourceRec,destRec,origin,0.0f,WHITE);
         }
         for(const auto& player : game.players){
            Color pColor = getRaylibColor(player.color);

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
               else if(t.state == TokenState::HOME_PATH){
                  int homeIdx = t.stepsTaken - 52;
                  if(homeIdx >= 0 && homeIdx < 5){
                     if(player.color == "RED"){
                     drawX = redHome[homeIdx].x;drawY = redHome[homeIdx].y;
                     }
                     else if(player.color == "GREEN"){
                        drawX = greenHome[homeIdx].x;drawY = greenHome[homeIdx].y;
                     }
                     else if(player.color == "YELLOW"){
                        drawX = yellowHome[homeIdx].x;drawY = yellowHome[homeIdx].y;
                     }
                     else if(player.color == "BLUE"){
                        drawX = blueHome[homeIdx].x;drawY = blueHome[homeIdx].y;
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
         DrawText(TextFormat("Turn: %s",game.players[game.currentplayerIndex].color.c_str()),20,20,20,getRaylibColor(game.players[game.currentplayerIndex].color));
         if(game.gameOver){
            DrawRectangle(0,350,800,100,Fade(BLACK,0.8f));
            DrawText("GAME OVER!",280,380,40,GREEN);
         }
         else if(game.needsToRoll){
            DrawText("Press SPACE to Roll",280,380,20,BLACK);
         }
         EndDrawing();
     }
     UnloadTexture(boardTexture);
     CloseWindow();
     return 0;
}