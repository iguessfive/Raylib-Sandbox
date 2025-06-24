// Boilerplate code for setting up a game loop & window

#include "raylib.h"
#include "raymath.h"

#include "debug.h"
#include <iostream>

static const int screenWidth = 1152;
static const int screenHeight = 648;

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
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();


}

