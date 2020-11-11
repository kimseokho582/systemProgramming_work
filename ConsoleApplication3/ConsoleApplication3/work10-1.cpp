#include <gl/glut.h>					
#include <gl/gl.h>						
#include <gl/glu.h>	

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 300, 300);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < 3; j++) {
            glPushMatrix();
            glColor3f(0.3 * j, 0.1 * i, 0.0);
            glTranslatef(0.2 * j, 0.2 * i, 0);
            glutSolidCube(0.1);
            glPopMatrix();
        }
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing");
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(MyDisplay);

    glutMainLoop();
    return 0;
}

