#pragma once
#include "Player.h"

class PlayerX : public Player
{
public:
    PlayerX();
    void draw() override;
protected:
    void initBuffer() override;
};

