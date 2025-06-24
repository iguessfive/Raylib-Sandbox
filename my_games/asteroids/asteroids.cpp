#include "raylib.h"
#include "raymath.h"

#include <iostream>

// Setting
#define WINDOW_WIDTH 1152
#define WINDOW_HEIGHT 648
#define BGCOLOR Color({0xF0, 0xF2, 0xF3, 0xFF}) // #F0F2F3
#define PLAYER_SPEED 400
#define LASER_SPEED 600
#define METEOR_TIME_DURATION 0.4f

constexpr int METEOR_SPEED_RANGE[] = {300, 400};

struct Sprite {
    Texture2D texture;
    Vector2 position;
    Vector2 velocity; // speed & direction
    Vector2 sizeRect;

    void update(float delta){};

    void draw() 
    {
        DrawTextureV(texture, position, WHITE);
    }
};

struct Bullet : Sprite
{
    Vector2 position = Vector2();
    Vector2 direction = Vector2();
    float speed = 200.0f;
};


struct Player : Sprite
{
    Vector2 direction;
    float speed;

    Player(Vector2 position = Vector2(), Vector2 direction = Vector2(), float speed = 300.0f) {
        this->texture = LoadTexture("my_games/asteroids/spaceship.png");
        this->sizeRect = Vector2({128.0f, 128.0f});
        this->position = position;
        this->direction = direction;
        this->speed = speed;
    }

    Player(float speed){};

    void update() 
    {
        // Input
        direction.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        direction.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);

        if (IsKeyDown(KEY_SPACE)) // Shoot
        {

        }

        // Movement
        direction = Vector2Normalize(direction);
        velocity = Vector2Scale(direction, speed);
        float delta = GetFrameTime();
        position += velocity * delta;

        // Keep in bounds
        position.x = Clamp(position.x, 0.0f, WINDOW_WIDTH - sizeRect.x);
        position.y = Clamp(position.y, 0.0f, WINDOW_HEIGHT - sizeRect.y);
    }


    ~Player() 
    {
        UnloadTexture(texture);
    }
};

struct Asteroid : Sprite
{
    Vector2 position = Vector2();
    Vector2 direction = Vector2();
    float speed = 200.0f;
};

struct Game {
    
    Game() // Default 
    {
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Asteroids");
        SetExitKey(KEY_ESCAPE);
    };
    
    void run()
    {
        // Setup Logic
        Player player{};
        player.position = Vector2{(WINDOW_WIDTH - player.sizeRect.x)/2.0f, (WINDOW_HEIGHT - player.sizeRect.y)/2.0f};

        // Game Loop
        while (!WindowShouldClose())
        {
            // Updating Logic
            player.update();

            // Rendering
            BeginDrawing();
            ClearBackground(BGCOLOR);

            player.draw();
            
            EndDrawing();
        };
        CloseWindow();
    };
}; 

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() 
{
    Game game{};
    game.run();
}

