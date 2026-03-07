#include "functions.h"

PixelVector reversePixelVector(PixelVector vec)
{
    return (PixelVector){-(vec.sX), -(vec.sY)};
}

Projection projectPolygon(Point* pts, int ax, int ay) 
{
    long long initialProj = (long long)pts[0].x * ax + (long long)pts[0].y * ay;
    Projection result = { initialProj, initialProj };
    for (int j = 1; j < 4; j++) 
    {
        long long proj = (long long)pts[j].x * ax + (long long)pts[j].y * ay;
        if (proj < result.min) result.min = proj;
        if (proj > result.max) result.max = proj;
    }
    return result;
}
Point getPointFromVector(Sprite sprite, PixelVector vec)
{
    return (Point){sprite.x + vec.sX, sprite.y + vec.sY};
}

bool hitboxColide(GameObject object1, GameObject object2)
{
    Hitbox h1 = object1.getCurrentCostume().hitbox;
    Hitbox h2 = object2.getCurrentCostume().hitbox;

    Point pts1[4] = {
        getPointFromVector(object1.getSprite(), h1.topLeft),
        getPointFromVector(object1.getSprite(), h1.topRight),
        getPointFromVector(object1.getSprite(), h1.bottomRight),
        getPointFromVector(object1.getSprite(), h1.bottomLeft)
    };
    Point pts2[4] = {
        getPointFromVector(object2.getSprite(), h2.topLeft),
        getPointFromVector(object2.getSprite(), h2.topRight),
        getPointFromVector(object2.getSprite(), h2.bottomRight),
        getPointFromVector(object2.getSprite(), h2.bottomLeft)
    };

    Point* shapes[2] = {pts1, pts2};

    for (int s = 0; s < 2; s++) 
    {
        for (int i = 0; i < 4; i++) 
        {
            Point p1 = shapes[s][i];
            Point p2 = shapes[s][(i + 1) % 4];
            int axisX = -(p2.y - p1.y);
            int axisY = (p2.x - p1.x);
            Projection res1 = projectPolygon(pts1, axisX, axisY);
            Projection res2 = projectPolygon(pts2, axisX, axisY);
            if (res1.max < res2.min || res2.max < res1.min) {
                return false; 
            }
        }
    }
    return true;
}
