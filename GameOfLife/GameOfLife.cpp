// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "LifeEngine.h"

int main()
{
    std::cout << "Hello World!\n";

    LifeEngine::ModernWindow w = LifeEngine::ModernWindow(800, 600, "res/shaders/Basic.shader");
}