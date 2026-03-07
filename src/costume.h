#pragma once
#include <vector>
#include <iostream>

//self defined
#include "structs.h"
class Costume
{
    public:
        std::vector<RelativePoint> points;
        Hitbox hitbox;
        Costume(std::string path);
        void addRelativePoint(int x, int y);
        void addHitbox(Hitbox hitbox);
        void addHitbox(PixelVector topLeft, PixelVector topRight, PixelVector bottomRight, PixelVector bottomLeft);
};