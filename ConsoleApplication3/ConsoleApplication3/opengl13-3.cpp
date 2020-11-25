#include <gl/glut.h>						
#include <gl/gl.h>							
#include <gl/glu.h>						
#include <iostream>
#include <math.h>
using namespace std;

void LineDraw(int x1, int y1, int x2, int y2) {
    int dx, dy, incrE, incrNE, D, x, y;
    dx = x2 - x1; dy = y2 - y1;
    D = 2 * dy - dx;
    incrE = 2 * dy;
    incrNE = 2 * dy - 2 * dx;
    x = x1; y = y1;
   
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    while (x < x2) {
        if (D <= 0) {
            D += incrE;
            x++;

        }
        else {
            D += incrNE;
            x++;
            y++;
        }
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }
}
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 0);
    for (int i = 0; i < 10000; i++) {
        LineDraw(0, i*0.1, 1000, 800+i*0.1);
        glFlush();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("OpenGL Drawing Example");
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000, 0.0, 800);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
}
