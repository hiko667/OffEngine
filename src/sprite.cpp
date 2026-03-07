#include "sprite.h"
#include "constants.h"


Sprite::Sprite()
{
    this->currentCostume = 0;
    this->x = MATRIX_WIDTH/2;
    this->y = MATRIX_HEIGHT/2;
}
Sprite::Sprite(int initialX, int initialY)
{
    this->currentCostume = 0;
    this->x = initialX;
    this->y = initialY;
}
void Sprite::addCostume(std::string pathToCostume)
{
    costumes.push_back(Costume(pathToCostume));
    if (!this->currentCostume) currentCostume = 0;
}
void Sprite::addCostume(Costume costume)
{
    costumes.push_back(costume);
    if (!this->currentCostume) currentCostume = 0;
}
void Sprite::move(PixelVector vec)
{
    this->x += vec.sX;
    this->y += vec.sY;
}
void Sprite::setPosition(Point point)
{
    this->x = point.x;
    this->y = point.y;
}

