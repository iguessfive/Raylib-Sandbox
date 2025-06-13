#include "raylib.h"

#include "debug.h"

int create_window(void);

int window_width = 1152;
int window_height = 648;

int main () 
{
    create_window();
}

int create_window(void)
{
    InitWindow(window_width, window_height, "Celeste Clone");

    while (!WindowShouldClose())
    {
        BeginDrawing(); // TItle screen logic
            ClearBackground(DARKGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}