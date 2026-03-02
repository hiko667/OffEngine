#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
#define MATRIX_HEIGHT 1080
#define MATRIX_WIDTH 1920


class Window
{
    public:
        static int Window_Height;
        static int Window_Width;
        static float Scale_Factor;
        Window(int height, int width, const char * name)
        {
            Window_Height = height;
            Window_Width = width;
            
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowSize(Window_Height, Window_Width);
            glutInitWindowPosition(100, 100);
            glutCreateWindow(name); 
            glutDisplayFunc(Window::display);
            glutMouseFunc(Window::mouse);
            glutReshapeFunc(Window::reshape);
            
            glutFullScreen();
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
            Scale_Factor = (float)viewWidth / 1920.0f;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0, 1920, 0, 1080);
            glMatrixMode(GL_MODELVIEW);
        }
        static void display() 
        {
            glClearColor( 0, 0, 0, 1 );
            glClear( GL_COLOR_BUFFER_BIT );


            draw_frame();
            glutSwapBuffers();
        }
        static void mouse(int button, int state, int x, int y)
        {
            
        }
        static void pixel(int x, int y)
        {
            glBegin(GL_POINTS);
            glPointSize(5.0f * Scale_Factor);
            glColor3ub(255, 255, 255);
            glVertex2i(x, y);
            glEnd();
        }
        static void draw_frame()
        {
            for (int x = 0; x <= 1920; x += 1) { 
                pixel(x, 0);
                pixel(x, 1079);
            }
            for (int y = 0; y <= 1080; y += 1) {
                pixel(0, y);
                pixel(1919, y);   
            }
        }
};
int Window::Window_Height = 0;
int Window::Window_Width = 0;
float Window::Scale_Factor = 0.0;


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    const char * name = "Kevin";
    Window w = Window(160, 120, name);
    return 0;
} 