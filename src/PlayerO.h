#pragma once
#include "Drawable.h"

class PlayerO : public Drawable
{
public:
    PlayerO();
    void draw() override;
private:
    void initBuffer() override;
    const float ROW_PADDING = 150.0f;
    const float COL_PADDING = 155.0f;
};
