
#include <gl/glut.h>					
#include <gl/gl.h>						
#include <gl/glu.h>	
#include <stdio.h>

GLfloat eX = .0;
GLfloat eY = .0;
GLfloat eZ = 1.0;
GLfloat aX = 0.0;
GLfloat aY = 0.0;
GLfloat aZ = 0.0;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eX, eY, eZ, aX, aY, aZ, 0, 1, 0);
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


void KB(unsigned char KeyPressed, int X, int Y) {

	switch (KeyPressed) {
	case 'q':
	case 'Q':
		eX += 0.1;
		break;
	case 'w':
	case 'W':
		eY += 0.1;
		break;
	case 'e':
	case 'E':
		eZ += 0.1;
		break;
	case 'a':
	case 'A':
		eX -= 0.1;
		break;
	case 's':
	case 'S':
		eY -= 0.1;
		break;
	case 'd':
	case 'D':
		eZ -= 0.1;
		break;

	case 'r':
	case 'R':
		aX += 0.1;
		break;
	case 't':
	case 'T':
		aY += 0.1;
		break;
	case 'y':
	case 'Y':
		aZ += 0.1;
		break;
	case 'f':
	case 'F':
		aX -= 0.1;
		break;
	case 'g':
	case 'G':
		aY -= 0.1;
		break;
	case 'h':
	case 'H':
		aZ -= 0.1;
		break;

	}
	glutPostRedisplay();
}

void MyReshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);


	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(KB);
	glutMainLoop();
	return 0;
}