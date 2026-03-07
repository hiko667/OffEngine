#include "gameObject.h"

GameObject::GameObject()
{
    this->sprite = Sprite();
}
void GameObject::addCostume(Costume costume)
{
    this->sprite.addCostume(costume); 
}
void GameObject::addCostume(std::string costume)
{
    this->sprite.addCostume(costume);
}
void GameObject::setPosition(Point point)
{
    this->sprite.setPosition(point);
}
void GameObject::move(PixelVector vec)
{
    this->sprite.move(vec);
}
Sprite GameObject::getSprite()
{
    return this->sprite;
}
Costume GameObject::getCurrentCostume()
{
    return this->sprite.costumes[this->sprite.currentCostume];
}
