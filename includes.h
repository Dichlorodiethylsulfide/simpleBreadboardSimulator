//
// Created by riki on 7/25/22.
//

#ifndef CLIONUNTITLED_INCLUDES_H
#define CLIONUNTITLED_INCLUDES_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;
using namespace sf;

#define PRINT(text, ...) \
printf(text,##__VA_ARGS__);\
fflush(stdout)

#endif //CLIONUNTITLED_INCLUDES_H
