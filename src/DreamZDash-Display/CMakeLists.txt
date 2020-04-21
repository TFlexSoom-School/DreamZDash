# Tristan Hilbert
# 4/21/2020
# Executable for Display
#


#Name Project and version
project(DreamZDisplay VERSION 1.0 LANGUAGES CXX)

# Find The SFML Libraries
find_library(LSFML_SYSTEM sfml-system)
find_library(LSFML_WINDOW sfml-window)
find_library(LSFML_GRAPHICS sfml-graphics)

# Add The Source Files
file(GLOB SRC *.cpp)

# Add The executable
add_executable(DreamZDisplay.out ${SRC})

# Link Them
target_link_libraries(DreamZDisplay.out ${LSFML_SYSTEM} ${LSFML_WINDOW} ${LSFML_GRAPHICS})
