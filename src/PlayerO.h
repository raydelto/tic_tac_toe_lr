#pragma once
#include "Player.h"

class PlayerO : public Player
{
public:
    PlayerO();
    void draw() override;
private:
    void initBuffer() override;
    const float ROW_PADDING = 150.0f;
    const float COL_PADDING = 155.0f;
};
