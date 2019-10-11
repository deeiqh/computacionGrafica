#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;

int ww = 700, wh = 400;

void setPixel(int x, int y);
void CirclePoints(int x, int y);
void circunferencia();
void setup();

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode as single-buffered and RGB color.
    glutInitWindowSize(ww, wh); // Set OpenGL window size.
    glutInitWindowPosition(200, 100); // Set position of OpenGL window upper-left corner.
    glutCreateWindow("Primitivas"); // Create OpenGL window with title.
    
    glutDisplayFunc(circunferencia); // Register display routine.

    setup(); // Register reshape routine.
    glutMainLoop();

    return 0;
}

void circunferencia()
{
    glClearColor(1,1,1, 1.0); // Set foreground color
    glColor3f(1,1,1); // Clear screen to background color.
    glClear(GL_COLOR_BUFFER_BIT);   //Flush created objects to the screen, i.e., force rendering.

    int r=100;
    int x, y, d;
    /* Valores iniciais */
    x = 0;
    y = r;
    d = 1 - r;
    CirclePoints(x+200, y+200);
    while (y > x){
        if (d < 0){
            /* Selecione E */
            d = d + 2 * x + 3;
            x++;
        }else{
            /* Selecione SE */
            d = d + 2 * (x - y) + 5;
            x++;
            y--;
        }/*end if*/
        CirclePoints(x+200, y+200);
    }/* end while */
    
    glFlush();
}

void CirclePoints(int x, int y)
{
    setPixel( x, y);
    setPixel( x, -y);
    setPixel(-x, y);
    setPixel(-x, -y);
    setPixel( y, x);
    setPixel( y, -x);
    setPixel(-y, x);
    setPixel(-y, -x);
}/* end CirclePoints */

void setPixel(int x, int y)
{
    glColor3f(0.0, 0.0, 1.0); //Set pixel to black
    glBegin(GL_POINTS);
    glVertex2i(x, y); //Set pixel coordinates
    glEnd();
}

void setup()
{
    glViewport(0, 0, ww, wh); // Set viewport size to be entire OpenGL window.
    glMatrixMode(GL_PROJECTION); // Set matrix mode to projection.
    glLoadIdentity(); // Clear current projection matrix to identity.
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh); // Specify the orthographic (or perpendicular) projection, i.e., define the viewing box.
    glMatrixMode(GL_MODELVIEW); // Set matrix mode to modelview.
}
