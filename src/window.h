#pragma once
#include "sprite.h"
#include "game.h"
#include "structs.h"

class Window
{
    public:
        static int Window_Height;
        static int Window_Width;
        static float Scale_Factor;
        static int Mouse_X;
        static int Mouse_Y;
        static int View_Width, View_Height, View_X, View_Y;
        static Game game;
        static Key globalKeyState;
        static Time T;
        Window(int height, int width, const char * name);
        static void init();
        static void reshape(int width, int height);
        static void display();
        static void mouse(int x, int y);
        static void mouseButtons(int button, int state, int x, int y);
        static void keyboard(unsigned char key, int x, int y);
        static void keyboardUp(unsigned char key, int x, int y);
        static void pixel(int x, int y, int red, int green, int blue);
        static void drawRectangle(int x, int y, int red, int green, int blue, int scale);
        static void drawFrame();
        static void drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue);
        static void drawSprite(Sprite sprite);
        static void drawAtScale(Sprite sprite, int scale);
        static void renderSprites();
        static void renderBackground();
};