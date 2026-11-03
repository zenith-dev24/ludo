#include <raylib.h>
#include <iostream>
#include "ludo.hpp"
#if defined(PLATFORM_WEB)
#include <emscripten.h>
#endif

using namespace std;
using namespace Ludo;

Vector2 mainPath[52] = {
{450.0f,100.0f},{450.0f,150.0f},{450.0f,200.0f},{450.0f,250.0f},{450.0f,300.0f},
{500.0f,350.0f},{550.0f,350.0f},{600.0f,350.0f},{650.0f,350.0f},{700.0f,350.0f},
{750.0f,350.0f},{750.0f,400.0f},{750.0f,450.0f},{700.0f,450.0f},{650.0f,450.0f},
{600.0f,450.0f},{550.0f,450.0f},{500.0f,450.0f},{450.0f,500.0f},{450.0f,550.0f},
{450.0f,600.0f},{450.0f,650.0f},{450.0f,700.0f},{450.0f,750.0f},{400.0f,750.0f},
{350.0f,750.0f},{350.0f,700.0f},{350.0f,650.0f},{350.0f,600.0f},{350.0f,550.0f},
{350.0f,500.0f},{300.0f,450.0f},{250.0f,450.0f},{200.0f,450.0f},{150.0f,450.0f},
{100.0f,450.0f},{50.0f,450.0f},{50.0f,400.0f},{50.0f,350.0f},{100.0f,350.0f},
{150.0f,350.0f},{200.0f,350.0f},{250.0f,350.0f},{300.0f,350.0f},{350.0f,300.0f},
{350.0f,250.0f},{350.0f,200.0f},{350.0f,150.0f},{350.0f,100.0f},{350.0f,50.0f},
{400.0f,50.0f},{450.0f,50.0f},
};
Vector2 redHome[5] = {{400,100},{400,150},{400,200},{400,250},{400,300}};
Vector2 greenHome[5] = {{100,400},{150,400},{200,400},{250,400},{300,400}};
Vector2 yellowHome[5] = {{400,700},{400,650},{400,600},{400,550},{400,500}};
Vector2 blueHome[5] = {{700,400},{650,400},{600,400},{550,400},{500,400}};

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
      int absPos = game.getAbsolutePosition(player.startPosition,t.stepsTaken);
      return mainPath[absPos];
   }
   else if(t.state == TokenState::HOME_PATH){
      int homeIdx = t.stepsTaken - 51;
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
   else if(t.state == TokenState::FINISHED){
      return{400.0f,400.0f};
   }
   return {0.0f,0.0f};
}
void drawDie(Rectangle rect, int face, bool isDiceRolling, Texture2D diceFaces[6]){
   int shownFace = isDiceRolling ? ((int)(GetTime() * 18) % 6) : (face > 0 ? face - 1 : 0);
   if(diceFaces[shownFace].id != 0){
      Rectangle sourceRec = {0.0f,0.0f,(float)diceFaces[shownFace].width,(float)diceFaces[shownFace].height};
      Vector2 origin = {0.0f,0.0f};
      DrawTexturePro(diceFaces[shownFace],sourceRec,rect,origin,0.0f,WHITE);
   }
}

int main(){
     const int boardSize = 800;
     const int screenWidth = 1100;
     const int screenHeight = 800;
     const int panelX = 820;

     InitWindow(screenWidth, screenHeight, "Ludo Game");
     SetTargetFPS(60);
     Texture2D boardTexture = LoadTexture("board.png");
      Texture2D diceFaces[6] = {
        LoadTexture("dice1.png"),
        LoadTexture("dice2.png"),
        LoadTexture("dice3.png"),
        LoadTexture("dice4.png"),
        LoadTexture("dice5.png"),
        LoadTexture("dice6.png")
     };

     int playerCount = 2;
     int selectedName = -1;
     int selectedColors[4] = {0,1,2,3};
     string playerNames[4] = {"Player 1","Player 2","Player 3","Player 4"};
     const char* colorNames[4] = {"RED","BLUE","YELLOW","GREEN"};
     Color playerColors[4] = {RED,BLUE,YELLOW,GREEN};
     int startPositions[4] = {0,13,26,39};
     bool setupComplete = false;
     bool diceIsRolling = false;
     double diceAnimationEnd = 0;
     LudoGame* game = nullptr;

      while(!WindowShouldClose()){
         Vector2 mousePos = GetMousePosition();
         if(!setupComplete){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
               if(CheckCollisionPointRec(mousePos,{(float)panelX+75,65,40,35})){
                  playerCount = playerCount > 2 ? playerCount - 1 : 2;
               }
               if(CheckCollisionPointRec(mousePos,{(float)panelX+140,65,40,35})){
                  playerCount = playerCount < 4 ? playerCount + 1 : 4;
               }
               for(int i = 0; i < playerCount; i++){
                  float rowY = 135 + i * 105;
                  if(CheckCollisionPointRec(mousePos,{(float)panelX+20,rowY,220,34})){
                     selectedName = i;
                  }
                  if(CheckCollisionPointRec(mousePos,{(float)panelX+250,rowY,35,34})){
                     selectedColors[i] = (selectedColors[i] + 1) % 4;
                  }
               }
               if(CheckCollisionPointRec(mousePos,{(float)panelX+20,650,260,55})){
                  game = new LudoGame(playerCount);
                  for(int i = 0; i < playerCount; i++){
                     game->players[i].name = playerNames[i];
                     game->players[i].color = colorNames[selectedColors[i]];
                     game->players[i].startPosition = startPositions[selectedColors[i]];
                  }
                  setupComplete = true;
               }
            }
            if(selectedName >= 0){
               int key = GetCharPressed();
               while(key > 0){
                  if(key >= 32 && key < 126 && playerNames[selectedName].size() < 15){
                  playerNames[selectedName] += (char)key;
                  key = GetCharPressed();
                  }
               }
               if(IsKeyPressed(KEY_BACKSPACE) && !playerNames[selectedName].empty()){
                  playerNames[selectedName].pop_back();
               }
               if(IsKeyPressed(KEY_ENTER)){
                  selectedName = -1;
               }
            }
         }
         else if(!game->gameOver){
            if(diceIsRolling && GetTime() >= diceAnimationEnd){ 
               diceIsRolling = false; game->rollDice(); 
            }
            bool clickedDie = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,{(float)panelX+20,380,100,100});
            bool pressedSpace = IsKeyPressed(KEY_SPACE);
            if(!diceIsRolling && (clickedDie || pressedSpace)){
               if(game->needsToRoll){
                  diceIsRolling = true;
                  diceAnimationEnd = GetTime() + 0.8;
               }
               else if(!game->hasValidMoves() && (clickedDie || pressedSpace)){
                  game->currentplayerIndex = (game->currentplayerIndex + 1) % game->players.size();
                  game->needsToRoll = true;
               }
            }
            if(!diceIsRolling && !game->needsToRoll && game->hasValidMoves() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mousePos.x < boardSize){
               for(int i = 0; i < 4; i++){
                  Vector2 tokenPos = getTokenDrawPosition(*game,game->currentplayerIndex,i);
                  if(CheckCollisionPointCircle(mousePos,tokenPos,18)){
                     game->tryMoveToken(i);
                     break;
                  }
               }
            }
         }
   
         BeginDrawing();
         ClearBackground(RAYWHITE);
         if(boardTexture.id != 0){
            Rectangle sourceRec = {0.0f,0.0f,(float)boardTexture.width,(float)boardTexture.height};
            Rectangle destRec = {0.0f,0.0f,(float)boardSize,(float)boardSize};
            Vector2 origin = {0.0f,0.0f};
            DrawTexturePro(boardTexture,sourceRec,destRec,origin,0.0f,WHITE);
         }
         for(int pIdx = 0; setupComplete && pIdx < game->players.size(); pIdx++){
            Color pColor = getRaylibColor(game->players[pIdx].color);
            for(int tIdx = 0; tIdx < 4; tIdx++){
               Vector2 tokenPos = getTokenDrawPosition(*game,pIdx,tIdx);
               DrawCircle(tokenPos.x,tokenPos.y,15,pColor);
               DrawCircleLines(tokenPos.x,tokenPos.y,15,BLACK);
            }
         }
         if(setupComplete){
            DrawRectangle(10,10,250,80,Fade(BLACK,0.7f));
            const player& current = game->players[game->currentplayerIndex];
            DrawText(TextFormat("Turn: %s",current.name.c_str()),20,20,20,getRaylibColor(current.color));
            if(game->needsToRoll){
               DrawText("Click die or press SPACE",20,50,18,WHITE);
            }
            else if(!game->hasValidMoves()){
               DrawText("No moves available",20,50,18,RED);
            }
            else{
               DrawText(TextFormat("Rolled: %d (click token)",game->currentRoll),20,50,18,WHITE);
            }
            if(game->gameOver){
               DrawRectangle(0,350,800,100,Fade(BLACK,0.8f));
               DrawText("GAME OVER!",280,380,40,GREEN);
            }
         }
         DrawRectangle(panelX,0,screenWidth-panelX,screenHeight,{248,248,248,255});
         DrawText("LUDO",panelX+20,18,30,BLACK);
         if(!setupComplete){
            DrawText("Players",panelX+20,72,20,BLACK);
            DrawRectangle(panelX+75,65,40,35,LIGHTGRAY); 
            DrawText("-",panelX+88,67,24,BLACK);
            DrawRectangle(panelX+140,65,40,35,LIGHTGRAY); 
            DrawText("+",panelX+151,67,24,BLACK);
            DrawText(TextFormat("%d",playerCount),panelX+120,72,20,BLACK);
            DrawText("Click name to edit; click color to cycle",panelX+20,112,14,DARKGRAY);
            for(int i = 0; i < playerCount; i++){
               float rowY = 135 + i * 105;
               DrawRectangle(panelX+20,rowY,220,34,WHITE);
               DrawRectangleLines(panelX+20,rowY,220,34,selectedName == i ? BLUE : GRAY);
               DrawText(playerNames[i].c_str(),panelX+28,rowY+8,18,BLACK);
               DrawRectangle(panelX+250,rowY,35,34,playerColors[selectedColors[i]]);
               DrawRectangleLines(panelX+250,rowY,35,34,BLACK);
               DrawText(colorNames[selectedColors[i]],panelX+20,rowY+42,15,BLACK);
            }
            DrawRectangle(panelX+20,650,260,55,{80,170,90,255});
            DrawText("START GAME",panelX+72,667,22,WHITE);
         }
         else{
            const player& current = game->players[game->currentplayerIndex];
            DrawText(current.color.c_str(),panelX+20,75,18,getRaylibColor(current.color));
            DrawText("Players",panelX+20,150,19,BLACK);
            for(int i = 0; i < game->players.size(); i++){
               DrawCircle(panelX+30,185+i*32,8,getRaylibColor(game->players[i].color));
               DrawText(game->players[i].name.c_str(),panelX+48,175+i*32,18,BLACK);
            }
            DrawText("DICE",panelX+20,350,18,BLACK);
            drawDie({(float)panelX+20,380,100,100},game->currentRoll,diceIsRolling,diceFaces);
            if(game->gameOver){
               DrawText("Winner!",panelX+145,410,24,GREEN);
            }
            else if(diceIsRolling){
               DrawText("Rolling...",panelX+20,510,18,BLACK);
            }
            else if(game->needsToRoll){
               DrawText("Click die or press SPACE",panelX+20,510,18,BLACK);
            }
            else if(!game->hasValidMoves()){
               DrawText(TextFormat("%d: no moves",game->currentRoll),panelX+20,510,18,RED);
               DrawText("Click die or press SPACE to pass",panelX+20,535,15,DARKGRAY);
            }
            else DrawText("Click a token",panelX+20,510,18,BLACK);
         }
         EndDrawing();
         #if defined(PLATFORM_WEB)
         emscripten_sleep(0); 
         #endif
      }
     if(game) delete game;
     for(int i = 0; i < 6; i++) UnloadTexture(diceFaces[i]);
     UnloadTexture(boardTexture);
     CloseWindow();
     return 0;
}
