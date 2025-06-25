#!/bin/bash

clang++ -std=c++20 my_games/asteroids/asteroids.cpp -o asteroids \
-I/opt/homebrew/include \
-L/opt/homebrew/lib -lraylib \
-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo



# BUILD_TYPE=${1:-release}

# if [[ "$BUILD_TYPE" == "debug" ]]; then
#   echo "Building debug version..."
#   clang++ -g -DDEBUG my_games/asteroids/asteroids.cpp -o sandbox \
#     -I/opt/homebrew/include \
#     -L/opt/homebrew/lib -lraylib \
#     -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
# else
#   echo "Building release version..."
#   clang++ -O3 -DNDEBUG xp/main.cpp -o asteroids \
#     -I/opt/homebrew/include \
#     -L/opt/homebrew/lib -lraylib \
#     -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
# fi
