#include "window.h"
#include <GL/gl.h>
#include <GL/glut.h>

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    const char * name = "Kevin";
    Window w = Window(160, 120, name);
    return 0;
}