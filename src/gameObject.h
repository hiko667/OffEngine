#pragma once
#include <iostream>
//self defined header files
#include "sprite.h"
#include "costume.h"
#include "structs.h"

class GameObject
{
    public:
        Sprite sprite;
        GameObject();
        void addCostume(Costume costume);
        void addCostume(std::string costume);
        void setPosition(Point point);
        void move(PixelVector vec);
        Sprite getSprite();
        Costume getCurrentCostume();
};
