# the min version of CMake this file is compatible with
# a required part of every CMake file
cmake_minimum_required(VERSION 2.8)

project("Qt Example Project")

# find the location of Qt header files and libraries
find_package(Qt5Widgets REQUIRED)

# later on, we'll use Qt Creator to build out our UI
# Qt Creator creates .ui files which will be preprocessed for us (that's what qt5_wrap_ui does)
# After preprocessing, a .h and .cpp file are produced for each .ui file
# we add the binary output directory as an include directory so that we can include the .h file later on
file(GLOB example_UIS *.ui)
qt5_wrap_ui(example_UIS ${example_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# tell CMake to compile every .cpp file in this directory and add it to an executable named `example`
file(GLOB example_SRC *.cpp)
add_executable(example ${example_SRC} ${example_UIS})

# this tells CMake where the header files and dynamic libraries are that we need
qt5_use_modules(example Widgets Core)
