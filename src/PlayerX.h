#pragma once
#include "Drawable.h"

class PlayerX : public Drawable
{
public:
    PlayerX();
    void draw() override;
private:
    // How far is one play from other
    const float ROW_PADDING = 150.0f;
    const float COL_PADDING = 160.0f;
    void initBuffer() override;
};

