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

# add the executable
add_executable(DreamZKernel src/DreamZKernel.cpp)