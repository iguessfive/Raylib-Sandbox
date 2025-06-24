#include "raylib.h"


// Camera
Camera2D camera = Camera2D();
// camera.zoom = 1;
// camera.target = player.position;
// camera.offset = Vector2({screenWidth/2.0f - player.sizeRect.x/2.0f, screenHeight/2.0f - player.sizeRect.y/2.0f});
// camera.rotation = 0.0f;

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