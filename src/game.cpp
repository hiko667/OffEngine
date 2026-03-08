#include "game.h"
#include "costume.h"
Game::Game()
{

}

std::vector<Sprite> Game::getSpritesToRender()
{
    std::vector<Sprite> sprites;
    for (auto object : activeGameObjects)
    {
        sprites.push_back(object.second.getSprite());
    }
    return sprites;
}
void Game::initializeObject(std::string name, std::vector<std::string> costumes)
{
    GameObject object = GameObject();
    for(std::string path : costumes)
    {
        if(this->costumes.find(path) == this->costumes.end())
        {
            Costume costume = Costume(path);
            costume.addHitbox((Hitbox){(PixelVector){-20, 20}, (PixelVector){20, 20}, (PixelVector){20, -20}, (PixelVector){-20, -20}});
            this->costumes.insert({path, costume});
            
            object.addCostume(costume);
        }
        else
        {
            object.addCostume(this->costumes.at(path));
        }
    }
    this->activeGameObjects.insert({name, object});
}
void Game::moveGameObject(std::string name, PixelVector vec)
{
    if(!(this->activeGameObjects.find(name) == this->activeGameObjects.end()))
    {
        this->activeGameObjects.at(name).move(vec);
    }
}
void Game::setGameObjectPosition(std::string name, Point point)
{
    if(!(this->activeGameObjects.find(name) == this->activeGameObjects.end()))
    {
        this->activeGameObjects.at(name).setPosition(point);
    }
}
void Game::notify(Key state, int mouseX, int mouseY)
{
    if(state.keysAscii[(int)'w']) this->moveGameObject("amogus", PixelVector {0, 10});
    if(state.keysAscii[(int)'a']) this->moveGameObject("amogus", PixelVector {-10, 0});
    if(state.keysAscii[(int)'s']) this->moveGameObject("amogus", PixelVector {0, -10});
    if(state.keysAscii[(int)'d']) this->moveGameObject("amogus", PixelVector {10, 0});
}

