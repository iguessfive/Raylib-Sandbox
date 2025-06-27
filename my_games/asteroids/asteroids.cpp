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

constexpr int ASTEROID_SPEED_RANGE[2] = {100, 250};

struct Sprite {
    Texture2D texture;
    Vector2 position;
    Rectangle Rect;
    Vector2 sizeRect;

    Sprite(){};
    Sprite(Vector2 position, Texture2D texture)
    {
        this->texture = texture;
        this->position = position;
        sizeRect = Vector2(texture.width, texture.height);
        Rect = Rectangle(position.x, position.y, sizeRect.x, sizeRect.y);
    }

    void draw() 
    {
        DrawTextureV(texture, position, WHITE);
    }

    Vector2 get_center() const
    {
        return Vector2({position.x / 2.0f, position.y / 2.0f});
    }
};

enum class ColliderType {Rectangle, Circle};

struct CollisionShape {
    ColliderType type; 
    Rectangle rect;
    Vector2 center; // circle
    float radius;

    CollisionShape()
    {
        // Adding the collision to obj
    }

    bool overlaps(const CollisionShape& other) const
    {
        switch (type)
        {
        case ColliderType::Rectangle:
            if (other.type == ColliderType::Rectangle)
            {
                return CheckCollisionRecs(rect, other.rect);
            }
            if (other.type == ColliderType::Circle)
            {
                return CheckCollisionCircleRec(other.center, other.radius, rect);
            }
            break;
        case ColliderType::Circle:
            if (other.type == ColliderType::Rectangle)
            {
                return CheckCollisionCircleRec(center, radius, other.rect);
            }
            if (other.type == ColliderType::Circle)
            {
                return CheckCollisionCircles(center, radius, other.center, other.radius);
            }
            break;
        default:
            std::cout << "Shape not found\n";
        }
        return false;
    }

    void update(Vector2 position, Vector2 size) 
    {
        switch (type)
        {
        case ColliderType::Rectangle:
            rect = Rectangle({position.x, position.y, size.x, size.y});
            break;
        case ColliderType::Circle:
            center = Vector2Add(position, Vector2Scale(size, 0.5f));
            break;
        default:
            std::cout << "Shape not found\n";
            break;
        }
    }
};

struct Bullet
{
    Sprite sprite;
    CollisionShape collider;
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
    CollisionShape collider;
    Vector2 velocity;
    Vector2 direction;
    float speed;

    std::vector<Bullet> bulletPool{};

    Player(Vector2 position = Vector2(), Vector2 direction = Vector2(), float speed = 300.0f) {
        sprite = Sprite(position, GetTexture("player"));
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
            Bullet newBullet = Bullet(
                // position: (28: player_size - 16: bullet_size) / 2 = 6
                Vector2Add(sprite.position, Vector2({6.0f, -10.0f})), GetTexture("bullet")
            );
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
    CollisionShape collider;
    Vector2 direction = Vector2({0, 1});
    float speed;
    Vector2 velocity;
    bool isOffScreen = false;
    float rotation;

    Asteroid(Sprite sprite)
    {
        this->sprite = sprite;
        speed = (float)GetRandomValue(ASTEROID_SPEED_RANGE[0], ASTEROID_SPEED_RANGE[1]);
        velocity = Vector2Scale(direction, speed);
        rotation = 0;
    }

    void update() 
    {
        float delta = GetFrameTime();
        sprite.position += velocity * delta;
        rotation += 40.0 * delta;

        if ((sprite.position.y - sprite.texture.height) > WINDOW_HEIGHT)
        {
            isOffScreen = true;
        }

        // Physic

    }

    void draw()
    {
        DrawTextureEx(
            sprite.texture, sprite.position, rotation, 1.0, WHITE
        );
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
                a.draw();
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
