#include <iostream>
#include "raylib.h"

#include "debug.h"

struct Player
{
    float speed = 120.0;
    Vector2 global_position = {0, 0};
    Vector2 size_rect = {100.0, 100.0};
    Vector2 position;
};

int create_window(void);
void handle_input(Player &player, float delta);

int screen_width = 1152;
int screen_height = 648;

int main () 
{
    InitDebugLogging();
    create_window();
}

void handle_input(Player &player, float delta)
{
    bool left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);

    if (left && !right) {
        player.position.x -= player.speed * delta;
    } else if (right && !left) {
        player.position.x += player.speed * delta;
    }
};

int create_window(void)
{
    InitWindow(screen_width, screen_height, "Celeste Clone");

    //region: player setup 
    Player player;
    player.global_position = Vector2{(float)screen_width/2.0f, (float)screen_height/2.0f};
    player.position = {
        (player.global_position.x + player.size_rect.x) / 2.0f,
        (player.global_position.y + player.size_rect.y) / 2.0f
    };
    //endregion

    while (!WindowShouldClose()) // main loop
    {
        float delta = GetFrameTime();
        handle_input(player, delta);
        
        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawRectangle(
                player.global_position.x, player.global_position.y, player.size_rect.x, player.size_rect.y, WHITE
            ); // render player shape
            DrawCircle(player.position.x, player.position.y, 10.0, BLACK);
            DrawCircle(player.global_position.x, player.global_position.y, 5.0, GOLD);
        EndDrawing();
    };

    CloseWindow();

    return 0;
}
