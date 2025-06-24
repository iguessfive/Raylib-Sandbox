#include "raylib.h"
#include "raymath.h"

#include "debug.h"
#include <iostream>

static const int screenWidth = 1152;
static const int screenHeight = 648;

struct Sprite
{
    /* data */
};
    

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() 
{
    #ifdef DEBUG
        InitDebugLogging();
    #endif

    InitWindow(screenWidth, screenHeight, "Sandbox");
    SetExitKey(KEY_ESCAPE);

    // Game Loop
    while (!WindowShouldClose())
    {

        // Rendering
        BeginDrawing();
        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();


}