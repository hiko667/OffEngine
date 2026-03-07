#pragma once
struct Time
{
    int time1, time2;
};

//to add handling of more keys just add them here
struct Key
{
    bool w,a,s,d;
    bool mouseLeft, mouseMiddle, mouseRight;
};

struct ColorRGB
{
    int r;
    int g;
    int b;
};

struct PixelVector // describes relative position of point to the origin point of sprites
{
    int sX; //shift X
    int sY; //shift Y
};

struct RelativePoint
{
    PixelVector shift;
    ColorRGB color;
};

struct Point
{
    int x;
    int y;
};
struct Hitbox
{
    PixelVector topLeft;
    PixelVector topRight;
    PixelVector bottomRight;
    PixelVector bottomLeft;
};

struct Projection {
    long long min;
    long long max;
};
