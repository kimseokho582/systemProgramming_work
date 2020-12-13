#include <gl/glut.h>						
#include <gl/gl.h>							
#include <gl/glu.h>						
#include <stdio.h>

float boundaryColor[3] = { 1.0,1.0,0.1 };
float fillColor[3] = { 1.0,0.1,0.1 };
int x = 4, y = 4;//시작

int myImg[7][8] = {
{ 1, 1, 1, 1, 1, 1, 1, 1},
{ 1, 1, 0, 0, 0, 0, 1, 1},
{ 1, 1, 0, 0, 0, 0, 0, 1},
{ 1, 1, 0, 0, 0, 0, 0, 1},
{ 1, 0, 0, 0, 0, 0, 1, 1},
{ 1, 0, 0, 0, 0, 0, 1, 1},
{ 1, 1, 1, 1, 1, 1, 1, 1}
};

int check[7][8] = { 0, }; // 칠한곳 체크

void drawPoint(int x, int y, float color[3]) { // 점찍기
    glPushMatrix();
    glPointSize(20);
    glBegin(GL_POINTS);
    glColor3fv(color);
    glVertex2f(x, y);
    glEnd();
  
    glFlush();
}

void drawBoundry() { //테두리 
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 8; j++) {
            if (myImg[i][j] == 1)
                drawPoint(i, j, boundaryColor);
        }
    }
}

void boundaryFill(int x, int y, float fillColor[3], float boundaryColor[3]) { 
    if ((myImg[x][y] == 0) && (check[x][y] == 0)) {
        drawPoint(x, y, fillColor);
        printf("x: %d, y: %d\n", x, y);
        check[x][y] = 1;
        boundaryFill(x + 1, y, fillColor, boundaryColor);
        boundaryFill(x - 1, y, fillColor, boundaryColor);
        boundaryFill(x, y + 1, fillColor, boundaryColor);
        boundaryFill(x, y - 1, fillColor, boundaryColor);

    }

}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBoundry();
    boundaryFill(x, y, fillColor, boundaryColor);

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(300, 400);
    glutCreateWindow("OpenGL Drawing Example");

    glClearColor(0.2, 0.2, 0.2, 0.0);
    gluOrtho2D(-2.0, 10.0, -2.0, 10.0);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
}

