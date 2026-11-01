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
Vector2 getTokenDrawPosition(LudoGame& game,int pIdx,int tIdx){
   const Ludo::player& player = game.players[pIdx];
   const Ludo::Token& t = player.tokens[tIdx];

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
      if(homeIdx>= 0 && homeIdx < 5){
         if(player.color == "RED"){
            return redHome[homeIdx];
         }
         if(player.color == "GREEN"){
            return greenHome[homeIdx];
         }
         if(player.color == "YELLOW"){
            return yellowHome[homeIdx];
         }
         if(player.color == "BLUE"){
            return blueHome[homeIdx];
         }
      }
   }
   return {400.0f,400.0f};
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
            DrawTexturePro(boardTexture,sourceRec,destRec,origin,0.0f,WHITE);
         }
         for(int pIdx = 0;pIdx < game.players.size();pIdx++){
            Color pColor = getRaylibColor(game.players[pIdx].color);
            for(int tIdx = 0;tIdx < 4;tIdx++){
               Vector2 pos = getTokenScreenPos(game,pIdx,tIdx);
               if(pos.x != 0 && pos.y != 0){
                  DrawCircle(pos.x,pos.y,15,pColor);
                  DrawCircleLines(pos.x,pos.y,15,BLACK);
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