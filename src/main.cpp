#include <iostream>
#include "raylib.h"

#include "debug.h"

int create_window(void);
void handle_input(Vector2 &position, float delta);

int screen_width = 1152;
int screen_height = 648;

float speed = 120.0;

int main () 
{
    InitDebugLogging();
    create_window();
}

void handle_input(Vector2 &position, float delta)
{
    bool left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);

    if (left && !right) {
        position.x -= speed * delta;
    } else if (right && !left) {
        position.x += speed * delta;
    }
}

int create_window(void)
{
    InitWindow(screen_width, screen_height, "Celeste Clone");

    //START setup for rendering character texture
    Texture2D character = LoadTexture("character/idle.png");

    int frame_width = character.width;
    int frame_height = character.height;

    Rectangle source_img = {0.0f, 0.0f, (float)frame_width, (float)frame_height};
    Vector2 position = {(float)screen_width/2.0f, (float)screen_height/2.0f};
    //END

    while (!WindowShouldClose()) // main loop
    {
        float delta = GetFrameTime();

        handle_input(position, delta);
        
        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawTextureRec(character, source_img, position, WHITE); // render texture
        EndDrawing();
    }
    
    UnloadTexture(character);

    CloseWindow();

    return 0;
}
