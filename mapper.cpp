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
                cout << "{" << mousePos.x << "f," << mousePos.y << "f}," << (clikedPoints.size() - 1) << '\n';
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
        }
} 