# Tristan Hilbert
# 1/14/2020
# Trying to use CMAKE to allow crossplat build process
#
#

# Specify version of CMAKE
cmake_minimum_required(VERSION 3.13)

# Specify project name and version
project(DreamZDash VERSION 1.0 LANGUAGES CXX)

# https://stackoverflow.com/questions/41333215/mingw-sh-exe-must-not-be-in-your-path
set(DCMAKE_SH="CMAKE_SH-NOTFOUND")

# Provide C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create The Other Executables
add_subdirectory(DreamZDash-Display)

# add the executable
#add_executable(DreamZKernel DreamZKernel.cpp)