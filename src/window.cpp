#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "constants.h"
#include "window.h"


int Window::Window_Height = 0;
int Window::Window_Width = 0;
float Window::Scale_Factor = 0.0;
int Window::Mouse_X = 0;
int Window::Mouse_Y = 0;
int Window::View_Height = 0;
int Window::View_Width = 0;
int Window::View_X = 0;
int Window::View_Y = 0;
Game Window::game = Game();
Key Window::globalKeyState = (Key){false, false, false, false};
Time Window::T = Time();
Window::Window(int height, int width, const char * name)
{
    Window::Window_Height = height;
    Window::Window_Width = width;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Window_Height, Window_Width);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(name); 
    glutDisplayFunc(Window::display);
    glutPassiveMotionFunc(Window::mouse);
    glutReshapeFunc(Window::reshape);
    glutKeyboardFunc(Window::keyboard);
    glutKeyboardUpFunc(Window::keyboardUp);
    init();
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();
}
//initialization functions. It will read files in the future, than forward them to the game
void Window::init()
{
    game.initializeObject("amogus", {"amogus.png"});
    
    game.initializeObject("sus", {"amogus.png"});

    game.setGameObjectPosition("sus", (Point){100, 200});
}
//event functions
void Window::reshape(int width, int height) 
{
    float targetRatio = 16.0f / 9.0f;
    int viewWidth, viewHeight, viewCenterX, viewCenterY;
    if ((float)width /height > targetRatio)
    {
        viewHeight = height;
        viewWidth = width * targetRatio;
    }
    else 
    {
        viewWidth = width;
        viewHeight = height;
    }
    viewCenterX = (width - viewWidth) / 2;
    viewCenterY = (height - viewHeight) / 2;
    glViewport(viewCenterX, viewCenterY, viewWidth, viewHeight);
    Scale_Factor = (float)viewWidth / (float)MATRIX_WIDTH;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, MATRIX_WIDTH, 0, MATRIX_HEIGHT);
    // glMatrixMode(GL_MODELVIEW); //line deleted for now, idk why fixes all the bad things in the world
    View_Height = viewHeight;
    View_Width = viewWidth;
    View_X = viewCenterX;
    View_Y = viewCenterY;
}
void Window::display() 
{
    if(T.time1 - T.time2 >= MILISECONDS_PER_FRAME)
    {
        //functions to clear background
        glClearColor( 0, 0, 0, 1 );
        glClear( GL_COLOR_BUFFER_BIT );
        drawFrame();
        
        game.notify(Window::globalKeyState);

        renderSprites();
        // game.moveGameObject("amogus", (PixelVector){5, 0});
        T.time2 = T.time1;
        glutSwapBuffers();
    }
    T.time1 = glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
}
void Window::mouse(int x, int y)
{
    float relativeX = x - View_X;
    float relativeY = y - View_Y;
    Mouse_X = (relativeX / View_Width) * MATRIX_WIDTH;
    Mouse_Y = (1.0f - (relativeY / View_Height)) * MATRIX_HEIGHT;
    if (Mouse_X < 0) Mouse_X = 0; if (Mouse_X > MATRIX_WIDTH) Mouse_X = MATRIX_WIDTH;
    if (Mouse_Y < 0) Mouse_Y = 0; if (Mouse_Y > MATRIX_HEIGHT) Mouse_Y = MATRIX_HEIGHT;
    // glutPostRedisplay(); //i dont know if we need ts
}
void Window::mouseButtons(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON) Window::globalKeyState.mouseLeft = (state == GLUT_DOWN);
    if(button == GLUT_RIGHT_BUTTON) Window::globalKeyState.mouseRight = (state == GLUT_DOWN);
    if(button == GLUT_MIDDLE_BUTTON) Window::globalKeyState.mouseMiddle = (state == GLUT_DOWN);
}
void Window::keyboard(unsigned char key, int x, int y)
{
    
    if(key == 'w') Window::globalKeyState.w = true;
    if(key=='a') Window::globalKeyState.a = true;
    if(key=='s') Window::globalKeyState.s = true;
    if(key=='d') Window::globalKeyState.d = true;
}
void Window::keyboardUp(unsigned char key, int x, int y)
{
    if(key == 'w') Window::globalKeyState.w = false;
    if(key=='a') Window::globalKeyState.a = false;
    if(key=='s') Window::globalKeyState.s = false;
    if(key=='d') Window::globalKeyState.d = false;
}
//drawing functions
void Window::pixel(int x, int y, int red = 255, int green = 255, int blue = 255)
{
    glBegin(GL_POINTS);
    glPointSize(POINT_SIZE * Scale_Factor);
    glColor3ub(red, green, blue);
    glVertex2i(x, y);
    glEnd();
}
void Window::drawFrame()
{
    for (int x = 0; x <= MATRIX_WIDTH; x += 1) { 
        pixel(x, 0);
        pixel(x, MATRIX_HEIGHT - 2);
    }
    for (int y = 0; y <= MATRIX_HEIGHT; y += 1) {
        pixel(0, y);
        pixel(MATRIX_WIDTH - 2, y);   
    }
}
void Window::drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps == 0) 
    {
        pixel(x1, y1, red, green, blue);
        return;
    }
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) 
    {
        pixel((int)(x + 0.5), (int)(y + 0.5), red, green, blue);
        x += xInc;
        y += yInc;
    }
}
void Window::drawSprite(Sprite sprite)
{
    for(RelativePoint point : sprite.costumes[sprite.currentCostume].points)
    {
        int pixelX = sprite.x + point.shift.sX;
        int pixelY = sprite.y + point.shift.sY;
        pixel(pixelX, pixelY, point.color.r, point.color.g, point.color.b);
    }
}
//rendering functions
void Window::renderSprites()
{
    for(Sprite sprite : game.getSpritesToRender())
    {
        drawSprite(sprite);
    }
}