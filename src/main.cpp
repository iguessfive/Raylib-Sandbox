#include "raylib.h"

#include "debug.h"
#include "projectile_game.cpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main () 
{
    #ifdef DEBUG
        InitDebugLogging();
    #endif 
    projectile_game();
}

