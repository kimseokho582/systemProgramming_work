#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.3, 0.3, 0.7);
	glutWireTeapot(1.0);
	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluPerspective(30, (GLdouble)w / (GLdouble)h, 8.0, 50.0);
	//glOrtho(-9.0, 9.0, -9.0, 9.0, -9.0, 9.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(.0, .0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glMatrixMode(GL_PROJECTION);
	//glOrtho(-9.0, 9.0, -9.0, 9.0, -9.0, 9.0);
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutMainLoop();
	return 0;
}
