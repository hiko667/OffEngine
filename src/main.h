#ifndef MAIN_H
#define MAIN_H
#define STB_IMAGE_IMPLEMENTATION
//includes
#include <STB/stb_image.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
//include self-defined header files
// #include "costume.h"
using namespace std;
//definitions
#define MATRIX_HEIGHT 1080
#define MATRIX_WIDTH 1920
#define POINT_SIZE 10.0f
#define FRAMES_PER_SECOND 30
#define MILISECONDS_PER_FRAME 1000/FRAMES_PER_SECOND

//structs
struct Time
{
    int time1, time2;
}; struct Time T;

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
    vector<RelativePoint> corners;
};

#endif