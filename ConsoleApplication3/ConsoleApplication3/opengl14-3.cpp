#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

static int SpinAngle = 0;
void InitLight() {
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 }; 	//조명 특성	
	GLfloat light0_diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat material_ambient[] = { 0.4, 0.4, 0.4, 1.0 };	//물체 특성
	GLfloat material_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glShadeModel(GL_SMOOTH);	//구로 셰이딩		
	glEnable(GL_DEPTH_TEST);	//깊이 버퍼 활성화
	glEnable(GL_LIGHTING);		//조명 활성화
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}

void MyDisplay() {
	GLfloat LightPosition[] = { 0.0, 0.0, 1.5, 1.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0.0, 0.0, -3.0);

	glPushMatrix();
	glRotatef(SpinAngle, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glTranslatef(0.0, 0.0, 1.5);

	glDisable(GL_LIGHTING);
	glColor3f(0.9, 0.9, 0.9);
	
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glRotatef(45, 1, 1, 0);
	glutSolidCube(0.3);// 집
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 1, 1, 0);
	glTranslatef(0.5, 0, 0);
	glScalef(1, 2, 1);
	glutSolidCube(0.3); // 나무
	glPopMatrix();

	glPopMatrix();
	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0., 0., 10.5,    0.0, 0.0, -10.0,    0.0, 1.0, 0.0);	//시점변환
}


void MyTimer(int Value) {
	SpinAngle = (SpinAngle - 15) % 360;
	glutPostRedisplay();
	glutTimerFunc(100, MyTimer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("openGL Sample Drawing");

	InitLight();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(100, MyTimer, 3);

	glutMainLoop();
	return 0;
}