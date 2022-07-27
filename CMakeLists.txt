cmake_minimum_required(VERSION 3.22)
project(clionUntitled)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-lsfml-system -lsfml-window -lsfml-graphics")

add_executable(clionUntitled main.cpp WindowManager.cpp WindowManager.h ResourceManager.cpp ResourceManager.h includes.h WindowMouse.cpp WindowMouse.h PartObject.cpp PartObject.h)
