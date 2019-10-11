#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;

int ww = 700, wh = 400;
int xi=350, yi=100, xf=400, yf=300;

void setPixel(int x, int y);
void linea();
void setup();

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode as single-buffered and RGB color.
    glutInitWindowSize(ww, wh); // Set OpenGL window size.
    glutInitWindowPosition(200, 100); // Set position of OpenGL window upper-left corner.
    glutCreateWindow("Primitivas"); // Create OpenGL window with title.
    
    glClearColor(1,1,1, 1.0); // Set foreground color
    glColor3f(1,1,1); // Clear screen to background color.
    glClear(GL_COLOR_BUFFER_BIT);   //Flush created objects to the screen, i.e., force rendering.

    glutDisplayFunc(linea); // Register display routine.
    
    glFlush();

    setup(); // Register reshape routine.
    glutMainLoop();

    return 0;
}

void linea()
{
    //un solo sentido de dibujo de líneas
    if (xf<xi && yf<yi){ 
        swap(xi,xf);
        swap(yi,yf);
    }
    else{
        if(xf>xi && yf<yi){
            swap(xi,xf);
            swap(yi,yf);
        }
    }
 
    int yi_, xi_, xf_;
    xi_ = xi;
    yi_ = yi;
    xf_ = xf;

    //mandamos a origen
    xf = xf-xi;
    yf = yf-yi;
    xi=0;
    yi=0;

    //mandamos a simetria
    if (xf<xi){
        if (yf-abs(xf) > 0){
            //xf=xi-(xf-xi);        
            xf=-xf;
            swap(xf,yf);
        }
        else{
            //xf=xi-(xf-xi); 
            xf=-xf;
        }
    }
    else{
        if (yf-xf > 0){
            swap(xf,yf);
        }
    }

    int dx, dy, incE, incNE, d, x, y;
    dx = xf - xi;
    dy = yf - yi;
    d = 2 * dy - dx; /* Valor inicial de d */
    incE = 2 * dy; /* Incremento de E */
    incNE = 2 * (dy - dx); /* Incremento de NE */
    x = xi;
    y = yi;
    setPixel(xi_, yi_);

    while (x < xf){
        if (d <= 0){
            /* Escolhe E */
            d = d + incE;
            x = x + 1;
        }else{
            /* Escolhe NE */
            d = d + incNE;
            x = x + 1;
            y = y + 1;
        }/* end if */
        if (xf_<xi_){//reconstruccion
            if (yf-abs(xf) > 0){          
                setPixel(xi_-y,x+yi_);
            }
            else{
                setPixel(xi_-x,y+yi_);
            }
        }
        else{
            if (yf-abs(xf) > 0){                
                setPixel(y+xi_, x+yi_);
            }
            else{
                setPixel(x+xi_, y+yi_);
            }
        }
    }/* end while */
    
}

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




 /*
    int xf_simetrica, yf_simetrica;
    if (xf<xi){
        xf_simetrica = abs(xf-xi)+xi;
        if (abs(yf-yi) - abs(xf-xi) > 0){
            xf_simetrica = abs(yf);
            yf_simetrica = xf_simetrica;
        }
        else{
            yf_simetrica = abs(yf);
        }
    }
    else{
        if (abs(yf-yi) - abs(xf-xi) > 0){
            xf_simetrica = abs(yf);
            yf_simetrica = abs(xf);
        }
        else{
            xf_simetrica = abs(xf);
            yf_simetrica = abs(yf);
        }
    }
*/
