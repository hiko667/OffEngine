#include "main.h"

// classes
class Costume
{
    public:
        vector<RelativePoint> points;
        Costume(string path)
        {
            int height, width, channels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
            if(data == NULL)
            {
                cerr << "Error reading file: " << path << endl;
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
        void addRelativePoint(int x, int y)
        {
            RelativePoint point;
            point.shift.sX = x;
            point.shift.sY = y;
            points.push_back(point);
        }

};

class Sprite
{
    public:
        int x,y;
        vector<Costume> costumes;
        int currentCostume;
        Sprite()
        {
            x = MATRIX_WIDTH/2;
            y = MATRIX_HEIGHT/2;
        }
        Sprite(int initialX, int initialY)
        {
            x = initialX;
            y = initialY;
        }
        void addCostume(string pathToCostume)
        {
            costumes.push_back(Costume(pathToCostume));
            if (!this->currentCostume) currentCostume = 0;
        }
        void addCostume(Costume costume)
        {
            costumes.push_back(costume);
            if (!this->currentCostume) currentCostume = 0;
        }
        void move(PixelVector vec)
        {
            this->x += vec.sX;
            this->y += vec.sY;
        }
        void setPosition(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

};

class GameObject
{
    public:
        Sprite sprite;
        GameObject(vector<string> costumes)
        {
            sprite = Sprite(MATRIX_WIDTH/2, MATRIX_HEIGHT/2);
            for(string costume : costumes)
            {
                sprite.addCostume(costume);
            }
        }
        void setPosition(int x, int y)
        {
            this->sprite.setPosition(x, y);
        }
        void move(PixelVector vec)
        {
            this->sprite.move(vec);
        }
        void addCostume(Costume costume)
        {
            this->sprite.addCostume(costume);
        }
        Sprite getSprite()
        {
            return this->sprite;
        }
};

class Game
{
    vector<Costume> gameCostumes;
    vector<GameObject> activeGameObjects;
    vector<GameObject> inactiveGameObjects;
    public:
        Game()
        {

        }
        vector<Sprite> getSpritesToRender()
        {
            vector<Sprite> sprites;
            for (GameObject object : activeGameObjects)
            {
                sprites.push_back(object.getSprite());
            }
            return sprites;
        }
        void initializeObject(vector<string> costumes)
        {
            GameObject object = GameObject(costumes);
        }
        
        
};

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
        //initialization functions
        static void init(int s)
        {

        }
        //event functions
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
            // glMatrixMode(GL_MODELVIEW); //line deleted for now, idk why fixes all the bad things in the world
            View_Height = viewHeight;
            View_Width = viewWidth;
            View_X = viewCenterX;
            View_Y = viewCenterY;
        }
        static void display() 
        {
            if(T.time1 - T.time2 >= MILISECONDS_PER_FRAME)
            {
                //functions to clear background
                glClearColor( 0, 0, 0, 1 );
                glClear( GL_COLOR_BUFFER_BIT );
                drawFrame();
                //here be all the graphic functions
                drawLine(0, 0, Mouse_X, Mouse_Y, 255, 255, 0);
                
                
                T.time2 = T.time1;
                glutSwapBuffers();
            }
            T.time1 = glutGet(GLUT_ELAPSED_TIME);
            glutPostRedisplay();
        }
        static void mouse(int x, int y)
        {
            float relativeX = x - View_X;
            float relativeY = y - View_Y;
            Mouse_X = (relativeX / View_Width) * MATRIX_WIDTH;
            Mouse_Y = (1.0f - (relativeY / View_Height)) * MATRIX_HEIGHT;
            if (Mouse_X < 0) Mouse_X = 0; if (Mouse_X > MATRIX_WIDTH) Mouse_X = MATRIX_WIDTH;
            if (Mouse_Y < 0) Mouse_Y = 0; if (Mouse_Y > MATRIX_HEIGHT) Mouse_Y = MATRIX_HEIGHT;
            // glutPostRedisplay(); //i dont know if we need ts
        }
        //drawing functions
        static void pixel(int x, int y, int red = 255, int green = 255, int blue = 255)
        {
            glBegin(GL_POINTS);
            glPointSize(POINT_SIZE * Scale_Factor);
            glColor3ub(red, green, blue);
            glVertex2i(x, y);
            glEnd();
        }
        static void drawFrame()
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
        static void drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue)
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
        static void drawSprite(Sprite sprite)
        {
            for(RelativePoint point : sprite.costumes[sprite.currentCostume].points)
            {
                int pixelX = sprite.x + point.shift.sX;
                int pixelY = sprite.y + point.shift.sY;
                pixel(pixelX, pixelY, point.color.r, point.color.g, point.color.b);
            }
        }
        //rendering functions
        static void renderSprites()
        {
            for(Sprite sprite : game.getSpritesToRender())
            {
                drawSprite(sprite);
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