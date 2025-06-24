
#include "raylib.h"
#include "raymath.h"

Vector2 GetVector(int NegX, int PosX, int NegY, int PosY)
{
    float DirX = IsKeyDown(PosX) - IsKeyDown(NegX);
    float DirY = IsKeyDown(PosY) - IsKeyDown(NegX);
    return Vector2Normalize(Vector2({DirX, DirY}));
}

// if (position.x > screenWidth)
// {
//     moveDirection.x *= -1;
// }


// void handle_input(Player &player, float delta)
// {
//     bool left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
//     bool right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
//     bool up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
//     bool down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);

//     if (left && !right) {
//         player.global_position.x -= player.speed * delta;
//     } else if (right && !left) {
//         player.global_position.x += player.speed * delta;
//     } else if (up && !down) {
//         player.global_position.y -= player.speed * delta;
//     } else if (down && !up) {
//         player.global_position.y += player.speed * delta;
//     } 
// };