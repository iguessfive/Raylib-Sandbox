#include "raylib.h"
#include <unordered_map>
#include <string>

static std::unordered_map<std::string, Texture2D> textureMap;
static std::unordered_map<std::string, Sound> soundMap;
static Music backgroundMusic;
static std::unordered_map<std::string, Font> fontMap;

void ImportTextures() 
{
    textureMap["player"] = LoadTexture("my_games/asteroids/spaceship.png");
    textureMap["asteroid"] = LoadTexture("my_games/asteroids/asteriod.png");
    textureMap["bullet"] = LoadTexture("my_games/asteroids/bullet.png");
};

void ImportFonts() 
{
    fontMap["space grotesk"] = LoadFontEx("my_games/asteroids/space_grotesk_font.ttf", 90.0f, NULL, 0);
}

void ImportAudio() 
{
    backgroundMusic = LoadMusicStream("my_games/asteroids/gravity_waves_track.ogg");
    soundMap["shoot"] = LoadSound("my_games/asteroids/shoot_sfx.ogg");
}

Texture2D GetTexture(const std::string& name) {
    if (textureMap.find(name) != textureMap.end()) {
        return textureMap[name];
    } else {
        TraceLog(LOG_WARNING, TextFormat("Texture '%s' not found!", name.c_str()));
        return {}; // return empty texture (safe fallback)
    }
}

Sound GetSound(const std::string& name) {
    if (soundMap.find(name) != soundMap.end()) {
        return soundMap[name];
    } else {
        TraceLog(LOG_WARNING, TextFormat("Sound '%s' not found!", name.c_str()));
        return {}; // return empty Sound
    }
}

void UnloadTexture()
{
    for (auto& element : textureMap) {
        const auto& value = element.second; // texture
        UnloadTexture(value);
    }    
}

void UnloadAudio()
{
    for (auto& element : soundMap) {
        UnloadSound(element.second);
    }
    UnloadMusicStream(backgroundMusic);
}

void UnloadFonts()
{
    UnloadFont(fontMap["space grotesk"]);
}