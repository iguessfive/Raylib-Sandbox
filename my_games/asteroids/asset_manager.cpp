
#include "raylib.h"
#include <unordered_map>
#include <string>

static std::unordered_map<std::string, Texture2D> textureMap;
static std::unordered_map<std::string, Font> fontMap;

void ImportTextures() 
{
    textureMap["player"] = LoadTexture("my_games/asteroids/spaceship.png");
    textureMap["asteroid"] = LoadTexture("my_games/asteroids/asteriod.png");
    textureMap["bullet"] = LoadTexture("my_games/asteroids/bullet.png");
};

void ImportFonts() 
{
    fontMap["space grotesk"] = LoadFont("my_games/asteroids/space_grotesk_font.ttf");
}

Texture2D GetTexture(const std::string& name) {
    if (textureMap.find(name) != textureMap.end()) {
        return textureMap[name];
    } else {
        TraceLog(LOG_WARNING, TextFormat("Texture '%s' not found!", name.c_str()));
        return {}; // return empty texture (safe fallback)
    }
}

void UnloadTexture()
{
    for (auto& element : textureMap) {
        const auto& value = element.second; // texture
        UnloadTexture(value);
    }    
}

void UnloadFonts()
{
    UnloadFont(fontMap["space grotesk"]);
}