#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"
#include "sprite.h"
#include "gameObject.h"
PixelVector reversePixelVector(PixelVector vec);
Projection projectPolygon(Point* pts, int ax, int ay); 
Point getPointFromVector(Sprite sprite, PixelVector vec);
Point getPointFromVector(Sprite sprite, PixelVector vec);
bool hitboxColide(GameObject object1, GameObject object2);
#endif