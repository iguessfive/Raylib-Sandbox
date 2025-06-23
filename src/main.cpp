#include "raylib.h"
#include "raymath.h"

#include "debug.h"
#include <iostream>

#include "input.cpp"

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

static const int screenWidth = 1152;
static const int screenHeight = 648;


struct Player
{
    Image sprite;
    Vector2 sizeRect = Vector2();
    Vector2 position = Vector2();
    Vector2 direction = Vector2();
    float speed;
};

struct Circle
{
    Vector2 position;
    float radius;
    Color color;
};

Circle circles[100]{};

void initCircles()
{
    for(int i = 0; i < 100; ++i)
    {
        circles[i].position = Vector2({(float)GetRandomValue(-2000, 2000), (float)GetRandomValue(-1000, 1000)});
        circles[i].radius = GetRandomValue(25, 100);
        circles[i].color = BLUE;
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() 
{
    #ifdef DEBUG
        InitDebugLogging();
    #endif
    
    Player player{};
    player.speed = 200.0f;
    player.sizeRect = Vector2({100.0f, 100.0f});
    
    InitWindow(screenWidth, screenHeight, "Sandbox");
    SetExitKey(KEY_ESCAPE);

    initCircles();

    // Camera
    Camera2D camera = Camera2D();
    camera.zoom = 1;
    camera.target = player.position;
    camera.offset = Vector2({screenWidth/2.0f - player.sizeRect.x/2.0f, screenHeight/2.0f - player.sizeRect.y/2.0f});
    camera.rotation = 0.0f;

    // Game Loop
    while (!WindowShouldClose())
    {
        player.direction.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        player.direction.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
        player.direction = Vector2Normalize(player.direction);

        float delta = GetFrameTime();
        player.position += player.direction * player.speed * delta;
        camera.target = player.position;

        int rotation_direction = IsKeyDown(KEY_S) - IsKeyDown(KEY_A);
        camera.rotation += rotation_direction * delta * 50.0f;

        int zoom_direction = IsKeyDown(KEY_W) - IsKeyDown(KEY_Q);
        camera.zoom += zoom_direction * delta * 2.0f;
        camera.zoom = Clamp(camera.zoom, 0.3f, 1.5f);

        // Rendering
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        for (const auto& c : circles)
        {
            DrawCircleV(c.position, c.radius, c.color);
        }
        DrawRectangleV(player.position, player.sizeRect, WHITE);
        EndMode2D;
        EndDrawing();
    }

    CloseWindow();
}

