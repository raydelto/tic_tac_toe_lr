#include "GamePadListener.h"
#include <iostream>


void GamePadListener::handleArrowPressed(bool pressed, std::string name)
{
    if(pressed)
    {
        std::cout << "Button " << name << "is  pressed" << std::endl;
    }
    else
    {
        std::cout << "Button " << name<< " is NOT pressed" << std::endl;
    }

}

void GamePadListener::up(bool pressed)
{
    handleArrowPressed(pressed,"up");
}

void GamePadListener::down(bool pressed)
{
    handleArrowPressed(pressed,"down");
}

void GamePadListener::left(bool pressed)
{
    handleArrowPressed(pressed,"left");
}

void GamePadListener::right(bool pressed)
{
    handleArrowPressed(pressed,"right");
}

