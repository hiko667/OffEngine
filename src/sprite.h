#pragma once
#include <iostream>
#include <vector>
//you know the deal, self defined includes
#include "costume.h"
#include "structs.h"

class Sprite
{
    public:
        int x,y;
        std::vector<Costume> costumes;
        int currentCostume;
        Sprite();
        Sprite(int initialX, int initialY);
        void addCostume(std::string pathToCostume);
        void addCostume(Costume costume);
        void move(PixelVector vec);
        void setPosition(Point point);
};

