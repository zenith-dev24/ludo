#include <raylib.h>
#include <iostream>
#include <vector>

using namespace std;
int main(){
        const int screenWidth = 800;
        const int screenHeight = 800;

        InitWindow(screenWidth,screenHeight,"Ludo Game");
        SetTargetFPS(60);

        Texture2D boardTexture = LoadTexture("board.png");
        vector <Vector2> clickedPoints;
        cout << "Vector2 mainPath[52] = {\n";
        
        while(!WindowShouldClose()){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Vector2 mousePos = GetMousePosition();
                clickedPoints.push_back(mousePos);
                cout << "{" << mousePos.x << "f," << mousePos.y << "f}," << (clickedPoints.size() - 1) << '\n';
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            Rectangle sourceRec = {0.0f,0.0f,(float)boardTexture.width,(float)boardTexture.height};
            Rectangle destRec = {0.0f,0.0f,(float)screenWidth,(float)screenHeight};
            DrawTexturePro(boardTexture,sourceRec,destRec,{0,0},0.0f,WHITE);
            for(size_t i = 0;i < clickedPoints.size();i++){
                DrawCircle(clickedPoints[i].x,clickedPoints[i].y,10,RED);
                DrawText(TextFormat("%d",i),clickedPoints[i].x - 5,clickedPoints[i].y - 5,10,BLACK);
            }
            EndDrawing();
        }
        cout << "};\n";
        UnloadTexture(boardTexture);
        CloseWindow();
        return 0;
}