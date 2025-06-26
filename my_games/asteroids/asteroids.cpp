#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <vector>

#include "asset_manager.cpp"
#include "timer.h"

// Setting
#define WINDOW_WIDTH 1152
#define WINDOW_HEIGHT 648
#define BGCOLOR Color({0xF0, 0xF2, 0xF3, 0xFF}) // #F0F2F3
#define PLAYER_SPEED 400
#define LASER_SPEED 600
#define ASTEROID_TIME_DURATION 0.4f

constexpr int ASTEROID_SPEED_RANGE[2] = {300, 400};

struct Sprite {
    Texture2D texture;
    Vector2 position;
    Vector2 sizeRect = Vector2({128.0f, 128.0f}); // default grid

    Sprite(){};
    Sprite(Vector2 position, Texture2D texture)
    {
        this->texture = texture;
        this->position = position;
    }

    void draw() 
    {
        DrawTextureV(texture, position, WHITE);
    }
};

struct Bullet
{
    Sprite sprite;
    Vector2 direction = Vector2({0, -1});
    float speed = 600.0f;
    Vector2 velocity = Vector2Scale(direction, speed);
    bool isActive = false;

    Bullet(){};
    Bullet(Vector2 position, Texture2D texture)
    {
        sprite.texture = texture;
        sprite.position = position;
    }

    void update()
    {
        float delta = GetFrameTime();
        sprite.position += velocity * delta;

        if (sprite.position.y + sprite.texture.height < 0.0f)
        {
            isActive = false;
        }
    }
};

struct Player
{
    Sprite sprite;
    Vector2 velocity;
    Vector2 direction;
    float speed;

    std::vector<Bullet> bulletPool{};

    Player(Vector2 position = Vector2(), Vector2 direction = Vector2(), float speed = 300.0f) {
        sprite.texture = GetTexture("player");
        sprite.position = position;
        this->direction = direction;
        this->speed = speed;
    }

    void update() 
    {
        // Input
        direction.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        direction.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);

        if (IsKeyPressed(KEY_SPACE)) // Shoot
        {
            Bullet newBullet = Bullet(Vector2Add(sprite.position, Vector2{46.0f, -20.0f}), GetTexture("bullet"));
            newBullet.isActive = true;
            bulletPool.push_back(newBullet);
            std::cout << bulletPool.size() << "\n";
        }

        // Movement
        direction = Vector2Normalize(direction);
        velocity = Vector2Scale(direction, speed);
        float delta = GetFrameTime();
        sprite.position += velocity * delta;

        // Keep in bounds
        sprite.position.x = Clamp(sprite.position.x, 0.0f, WINDOW_WIDTH - sprite.sizeRect.x);
        sprite.position.y = Clamp(sprite.position.y, 0.0f, WINDOW_HEIGHT - sprite.sizeRect.y);
    }
};

struct Asteroid
{
    Sprite sprite;
    Vector2 direction = Vector2({0, 1});
    float speed = 200.0f;
    Vector2 velocity = Vector2Scale(direction, speed);
    bool isOffScreen = false;

    Asteroid(){};
    Asteroid(Sprite sprite)
    {
        this->sprite = sprite;
    }

    void update() 
    {
        float delta = GetFrameTime();
        sprite.position += velocity * delta;

        if ((sprite.position.y - sprite.texture.height) > WINDOW_HEIGHT)
        {
            isOffScreen = true;
        }
    }
};

struct Game {
    
    std::vector< Asteroid> asteroidPool{};

    Game() // Default 
    {
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Asteroids");
        SetExitKey(KEY_ESCAPE);
    };

    Timer CreateAsteroidSpawnTimer() {
        Timer spawnAsteroidTimer = Timer(
        ASTEROID_TIME_DURATION,
        true,
        true,
        [this]() 
        {
            float x = static_cast<float>(GetRandomValue(0, WINDOW_WIDTH - 128));
            Vector2 spawnPosition = {x, -128.0f}; // Off-screen top
            Sprite asteroidSprite = Sprite({spawnPosition, GetTexture("asteroid")});
            Asteroid newAsteroid(asteroidSprite);
            asteroidPool.push_back(newAsteroid);
        });
        return spawnAsteroidTimer;
    }
    
    void Run()
    {
        // Load Assets
        ImportTextures();
        // Setup Logic
        Player player{};
        player.sprite.position = Vector2{
            (WINDOW_WIDTH - player.sprite.sizeRect.x)/2.0f, (WINDOW_HEIGHT - player.sprite.sizeRect.y)/2.0f
        };

        Timer asteroidSpawnTimer = CreateAsteroidSpawnTimer();

        // Game Loop
        while (!WindowShouldClose())
        {
            // Updating Logic
            player.update();
            asteroidSpawnTimer.update();
            for (Asteroid &a : asteroidPool)
            {
                a.update();
            }
            for (Bullet &b : player.bulletPool)
            {
                if (b.isActive)
                {
                    b.update();
                }
            }
            // Once condition is true, the elment in array will be removed
            std::erase_if(player.bulletPool, [](const Bullet& b) { return !b.isActive; });
            std::erase_if(asteroidPool, [](const Asteroid& a) { return a.isOffScreen; });

            // Rendering
            BeginDrawing();
            ClearBackground(BGCOLOR);

            player.sprite.draw();
            for (Asteroid &a : asteroidPool)
            {
                a.sprite.draw();
            }
            for (Bullet &b : player.bulletPool)
            {
                if (b.isActive)
                {
                    b.sprite.draw();
                }
            }

            EndDrawing();
        };
        // Unload Assets
        UnloadTexture();
        CloseWindow();
    };
}; 

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() 
{
    Game game{};
    game.Run();
}
