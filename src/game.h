#pragma once
#include <unordered_map>
#include <vector>
#include <iostream>
#include "gameObject.h"
#include "structs.h"
#include "sprite.h"
class Game
{
    public:
        std::unordered_map<std::string, Costume> costumes;
        std::unordered_map<std::string, GameObject> activeGameObjects;
        std::unordered_map<std::string, GameObject> inactiveGameObjects;
        Game();
        std::vector<Sprite> getSpritesToRender();
        void initializeObject(std::string name, std::vector<std::string> costumes);
        void moveGameObject(std::string name, PixelVector vec);
        void setGameObjectPosition(std::string name, Point point);
        void notify(Key state, int mouseX, int mouseY);
};

