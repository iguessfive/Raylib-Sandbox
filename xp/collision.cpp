
#include "raylib.h"

Rectangle r1 = Rectangle({0, 0, 50, 50});
Rectangle r2 = Rectangle({500, 200, 200, 200});

int collision() {

    r1.x = GetMouseX();
    r1.y = GetMouseY();
    bool hasCollided = CheckCollisionRecs(r1, r2);

    //Rendering
    DrawRectangleRec(r1, WHITE);
    DrawRectangleRec(r2, RED);
    if (hasCollided)
    {
        DrawRectangleRec(GetCollisionRec(r1, r2), YELLOW);
    }
}