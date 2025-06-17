#!/bin/bash

BUILD_TYPE=${1:-release}

if [[ "$BUILD_TYPE" == "debug" ]]; then
  echo "Building debug version..."
  clang++ -g -DDEBUG src/main.cpp -o sandbox \
    -I/opt/homebrew/include \
    -L/opt/homebrew/lib -lraylib \
    -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
else
  echo "Building release version..."
  clang++ -O3 -DNDEBUG src/main.cpp -o sandbox \
    -I/opt/homebrew/include \
    -L/opt/homebrew/lib -lraylib \
    -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
fi
