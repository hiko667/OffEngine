#define STB_IMAGE_IMPLEMENTATION
#include "costume.h"
#include <STB/stb_image.h>

Costume::Costume(std::string path)
{
    int height, width, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    if(data == NULL)
    {
        //error handling to be added i guess
        return;
    }
    int centerX = width / 2;
    int centerY = height / 2;
    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            int index = (y * width + x) * 4;
            unsigned char r = data[index];
            unsigned char g = data[index + 1];
            unsigned char b = data[index + 2];
            unsigned char a = data[index + 3];
            if (a > 0) 
            {
                RelativePoint rp;
                rp.shift.sX = x - centerX;
                rp.shift.sY = y - centerY;
                rp.color.r = (int)r;
                rp.color.g = (int)g;
                rp.color.b = (int)b;
                points.push_back(rp);
            }
        }
    }
    stbi_image_free(data);
}
void Costume::addRelativePoint(int x, int y)
{
    RelativePoint point;
    point.shift.sX = x;
    point.shift.sY = y;
    points.push_back(point);
}
void Costume::addHitbox(Hitbox hitbox)
{
    this->hitbox = hitbox;
}
void Costume::addHitbox(PixelVector topLeft, PixelVector topRight, PixelVector bottomRight, PixelVector bottomLeft)
{
    this->hitbox = (Hitbox){topLeft, topRight, bottomRight, bottomLeft};
}

