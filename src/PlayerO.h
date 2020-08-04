#pragma once
#include "Player.h"

class PlayerO : public Player
{
public:
    PlayerO();
    void draw() override;
private:
    void initBuffer() override;
    const float ROW_PADDING = 200.0f;
    const float COL_PADDING = 157.0f;
};
