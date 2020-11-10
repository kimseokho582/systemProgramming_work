#include <Windows.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { 0.9, 0.9, 0.9, 0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

GLfloat MyVertices[8][3] = { {-0.25,-0.25,0.25}, {-0.25,0.25,0.25}, {0.25,0.25,0.25}, {0.25,-0.25,0.25},
{-0.25,-0.25,-0.25}, {-0.25,0.25,-0.25}, {0.25,0.25,-0.25}, {0.25,-0.25,-0.25} };
//GLfloat MyVertices[8][3] = {{-0.025,-0.025,0.025}, {-0.025,0.025,0.025}, {0.025,0.025,0.025}, {0.025,-0.025,0.025}, 
//{-0.025,-0.025,-0.025}, {-0.025,0.025,-0.025}, {0.025,0.025,-0.025}, {0.025,-0.025,-0.025}};

//GLfloat MyColors[8][3]={{0.2,0.2,0.2}, {1.0,0.0,0.0}, {1.0, 1.0, 0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
//{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};
GLfloat MyColors[8][3] = { {0.,0.,0.8}, {0.8,0.8,0.}, {0.8,0.8,0.}, {0.8,0.,0.}, {0.2,0.2,0.2},
{0.2,0.2,0.2}, {0.2,0.2,0.8}, {0.2,0.2,0.2} };

//GLubyte MyVertexList[24]={0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4}; //ori
//GLubyte MyVertexList[24]={0,3,2,1, 2,3,7,6, 1,2,6,5, 0,4,7,3, 4,5,6,7, 0,1,5,4};
GLubyte MyVertexList[24] = { 0,4,7,3, 4,5,6,7, 0,1,5,4, 0,3,2,1, 2,3,7,6, 1,2,6,5 };

void MyDisplay() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glCullFace(GL_BACK);

	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_LINE);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, MyVertices);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.5, 0.5, 0.5, .0, .0, .0, 0.0, 1.0, 0.0);

	glutWireTeapot(0.2);
	//for(GLint i = 0; i < 6; i++) 					

	GLint i = 0;
	i = 0;
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	i = 1;
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	i = 2;
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	i = 3;
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	i = 4;
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	i = 5;
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);

	glFlush();
}
/*
void MyDisplay( ){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );
	gluLookAt(0.0, 0.0, 2.0,    0.0, 0.0, 0.0,      0.0, 1.0, 0.0);
	glutSolidTeapot(0.5);
	glFlush();
}
*/

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	//gluPerspective(30, 1.0, -10.0, 50.0);	
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glClearColor(0.4, 0.4, 0.4, 0.0);
	//InitLight( );

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutMainLoop();
	return 0;

}