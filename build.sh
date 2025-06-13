#!/bin/bash

clang++ src/main.cpp -o celesteclone \
-I/opt/homebrew/include \
-L/opt/homebrew/lib -lraylib \
-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
