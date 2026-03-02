#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
#define MATRIX_HEIGHT 1080
#define MATRIX_WIDTH 1920
#define POINT_SIZE 10.0f
class Window
{
    public:
        static int Window_Height;
        static int Window_Width;
        static float Scale_Factor;
        static int Mouse_X;
        static int Mouse_Y;
        static int View_Width, View_Height, View_X, View_Y;
        Window(int height, int width, const char * name)
        {
            Window_Height = height;
            Window_Width = width;
            
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowSize(Window_Height, Window_Width);
            glutInitWindowPosition(100, 100);
            glutCreateWindow(name); 
            glutDisplayFunc(Window::display);
            glutPassiveMotionFunc(Window::mouse);
            glutReshapeFunc(Window::reshape);
            glutFullScreen();
            glutSetCursor(GLUT_CURSOR_NONE);
            glutMainLoop();
        }
        static void reshape(int width, int height) 
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
            glMatrixMode(GL_MODELVIEW);
            View_Height = viewHeight;
            View_Width = viewWidth;
            View_X = viewCenterX;
            View_Y = viewCenterY;
        }
        static void display() 
        {
            glClearColor( 0, 0, 0, 1 );
            glClear( GL_COLOR_BUFFER_BIT );
            
            draw_frame();
            draw_line(Mouse_X, Mouse_Y, 0, 0, 255, 0, 0);
            glutSwapBuffers();
        }
        static void mouse(int x, int y)
        {
            float relativeX = x - View_X;
            float relativeY = y - View_Y;
            Mouse_X = (relativeX / View_Width) * MATRIX_WIDTH;
            Mouse_Y = (1.0f - (relativeY / View_Height)) * MATRIX_HEIGHT;
            if (Mouse_X < 0) Mouse_X = 0; if (Mouse_X > MATRIX_WIDTH) Mouse_X = MATRIX_WIDTH;
            if (Mouse_Y < 0) Mouse_Y = 0; if (Mouse_Y > MATRIX_HEIGHT) Mouse_Y = MATRIX_HEIGHT;
            glutPostRedisplay();
        }
        static void pixel(int x, int y, int red = 255, int green = 255, int blue = 255)
        {
            glBegin(GL_POINTS);
            glPointSize(POINT_SIZE * Scale_Factor);
            glColor3ub(red, green, blue);
            glVertex2i(x, y);
            glEnd();
        }
        static void draw_frame()
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
        static void draw_line(int x1, int y1, int x2, int y2, int red, int green, int blue)
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

            for (int i = 0; i <= steps; i++) {
                pixel((int)(x + 0.5), (int)(y + 0.5), red, green, blue);
                x += xInc;
                y += yInc;
            }
        }

};


int Window::Window_Height = 0;
int Window::Window_Width = 0;
float Window::Scale_Factor = 0.0;
int Window::Mouse_X = 0;
int Window::Mouse_Y = 0;
int Window::View_Height = 0;
int Window::View_Width = 0;
int Window::View_X = 0;
int Window::View_Y = 0;

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    const char * name = "Kevin";
    Window w = Window(160, 120, name);
    return 0;
} 