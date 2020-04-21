#!/bin/bash

# cmake for the good stuff
cmake -S ./src/ -B ./build/

# Copy The PNG files
mkdir ./build/DreamZDash-Display/assets
cp ./assets/*.png ./build/DreamZDash-Display/assets

# Make The Files Once Done
cd ./build
make