#include <gl/glut.h>						
#include <gl/gl.h>							
#include <gl/glu.h>						
#include <iostream>
#include <math.h>
using namespace std;

void LineDraw(int x1, int y1, int x2, int y2) {
    float m, y;
    float dx, dy;
    dx = x2 - x1; dy = y2 - y1;
    m = dy / dx;
    y = y1;
  
    for (int x = x1; x < x2; x++) {
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
        y += m;
    }
}


void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 0);
    LineDraw(0, 0, 1000, 800);
    glFlush();
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 800);
    glutCreateWindow("OpenGL Drawing Example");

    glClearColor(0.5, 0.5, 0.5, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 100, 0.0, 80);

    glutDisplayFunc(MyDisplay);
    glutMainLoop();
}
