#include <Windows.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

GLfloat MyVertices[8][3] = { {-0.25,-0.25,0.25}, {-0.25,0.25,0.25}, {0.25,0.25,0.25}, {0.25,-0.25,0.25},
{-0.25,-0.25,-0.25}, {-0.25,0.25,-0.25}, {0.25,0.25,-0.25}, {0.25,-0.25,-0.25} };
GLfloat MyColors[8][3] = { {0.,0.,1}, {1,1,0.}, {1,1,0.}, {1,0.,0.}, {0,0,0},
{0.0,0.0,0.0}, {0.0,0.0,1}, {0.0,0.0,0.0} };
GLubyte MyVertexList[24] = { 0,4,7,3, 4,5,6,7, 0,1,5,4, 0,3,2,1, 2,3,7,6, 1,2,6,5 };

void MyDisplay() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, MyVertices);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1.0, 1.0, 1, .0, .0, .0, 0.0, 1.0, 0.0);
	for (GLint i = 0; i < 6; i++) {
		//if (i != 4)  //�ĸ� ���� Ȯ���� ���� index 4 ���� �׸��� ����
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);	
	}
	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, 1.0, 0.5, 3.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutMainLoop();
	return 0;
}