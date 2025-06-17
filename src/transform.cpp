#include "raylib.h"

int screen_width = 1152;
int screen_height = 648;

const Vector2 origin = {screen_width/2.0f, screen_height/2.0f};

struct Player
{
    float speed = 120.0;
    Vector2 size_rect = {50.0f, 50.0f};
    Vector2 global_position = origin;
    Vector2 position = global_position;
};

int create_window(void)
{
    InitWindow(screen_width, screen_height, "Celeste Clone");

    //region: player setup 
    Player player;
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
            DrawCircle(player.position.x, player.position.y, 5.0, BLACK);
            DrawCircle(player.global_position.x, player.global_position.y, 5.0, GOLD);
        EndDrawing();
    };

    CloseWindow();

    return 0;
}

void handle_input(Player &player, float delta)
{
    bool left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    bool up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    bool down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);

    if (left && !right) {
        player.global_position.x -= player.speed * delta;
    } else if (right && !left) {
        player.global_position.x += player.speed * delta;
    } else if (up && !down) {
        player.global_position.y -= player.speed * delta;
    } else if (down && !up) {
        player.global_position.y += player.speed * delta;
    } 
};