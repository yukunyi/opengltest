// Draw the "dot plots" of a function
//P52 in <Computer Graphics Using OpenGL(Second Edition)>

#include<math.h>
#include<GL/glut.h>
#include<iostream>

using namespace std;

const int screenWidth = 640; // width of screen window in pixels
const int screenHeight = 480; // height of screen window in pixels

//����һ�����ڴ�Ż���6����Ľṹ��
struct Gl3DRect {
	GLfloat facadeTopLeft[3];
	GLfloat facadeTopRight[3];
	GLfloat facadeBottomLeft[3];
	GLfloat facadeBottomRight[3];
	GLfloat backFacadeTopLeft[3];
	GLfloat backFacadeTopRight[3];
	GLfloat backFacadeBottomLeft[3];
	GLfloat backFacadeBottomRight[3];

	GLfloat topColor[3];
	GLfloat rightColor[3];
	GLfloat leftColor[3];
	GLfloat bottomColor[3];
	GLfloat facadeColor[3];
	GLfloat backFacadeColor[3];
};

void draw3DRect(Gl3DRect rect) {

	//���Ƶ�һ�棨ǰ�棩
	glColor3f(rect.facadeColor[0], rect.facadeColor[1], rect.facadeColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.facadeTopLeft);
	glVertex3fv(rect.facadeTopRight);
	glVertex3fv(rect.facadeBottomLeft);
	glVertex3fv(rect.facadeBottomRight);
	glEnd();

	//���Ƶڶ��棨���棩
	glColor3f(rect.backFacadeColor[0], rect.backFacadeColor[1],
			rect.backFacadeColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.backFacadeTopLeft);
	glVertex3fv(rect.backFacadeTopRight);
	glVertex3fv(rect.backFacadeBottomLeft);
	glVertex3fv(rect.backFacadeBottomRight);
	glEnd();

	//���Ƶ����棨���棩
	glColor3f(rect.topColor[0], rect.topColor[1], rect.topColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.facadeTopLeft);
	glVertex3fv(rect.facadeTopRight);
	glVertex3fv(rect.backFacadeTopLeft);
	glVertex3fv(rect.backFacadeTopRight);
	glEnd();

	//���Ƶ����棨���棩
	glColor3f(rect.bottomColor[0], rect.bottomColor[1], rect.bottomColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.facadeBottomLeft);
	glVertex3fv(rect.facadeBottomRight);
	glVertex3fv(rect.backFacadeBottomLeft);
	glVertex3fv(rect.backFacadeBottomRight);
	glEnd();

	//���Ƶ����棨���棩
	glColor3f(rect.leftColor[0], rect.leftColor[1], rect.leftColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.facadeTopLeft);
	glVertex3fv(rect.facadeBottomLeft);
	glVertex3fv(rect.backFacadeTopLeft);
	glVertex3fv(rect.backFacadeBottomLeft);
	glEnd();

	//���Ƶ����棨���棩
	glColor3f(rect.rightColor[0], rect.rightColor[1], rect.rightColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.facadeTopRight);
	glVertex3fv(rect.facadeBottomRight);
	glVertex3fv(rect.backFacadeTopRight);
	glVertex3fv(rect.backFacadeBottomRight);
	glEnd();
}

Gl3DRect create3DRectPoints(GLfloat startPoint[3], GLfloat xLength,
		GLfloat yLength, GLfloat zLength) {
	Gl3DRect rect;
	rect.backFacadeBottomLeft[0] = startPoint[0];
	rect.backFacadeBottomLeft[1] = startPoint[1];
	rect.backFacadeBottomLeft[2] = startPoint[2];
	rect.backFacadeBottomRight[0] = startPoint[0] + xLength;
	rect.backFacadeBottomRight[1] = startPoint[1];
	rect.backFacadeBottomRight[2] = startPoint[2];

	rect.backFacadeTopLeft[0] = startPoint[0];
	rect.backFacadeTopLeft[1] = startPoint[1] + yLength;
	rect.backFacadeTopLeft[2] = startPoint[2];
	rect.backFacadeTopRight[0] = startPoint[0] + xLength;
	rect.backFacadeTopRight[1] = startPoint[1] + yLength;
	rect.backFacadeTopRight[2] = startPoint[2];

	rect.facadeBottomLeft[0] = startPoint[0];
	rect.facadeBottomLeft[1] = startPoint[1];
	rect.facadeBottomLeft[2] = startPoint[2] + zLength;
	rect.facadeBottomRight[0] = startPoint[0] + xLength;
	rect.facadeBottomRight[1] = startPoint[1];
	rect.facadeBottomRight[2] = startPoint[2] + zLength;

	rect.facadeTopLeft[0] = startPoint[0];
	rect.facadeTopLeft[1] = startPoint[1] + yLength;
	rect.facadeTopLeft[2] = startPoint[2] + zLength;
	rect.facadeTopRight[0] = startPoint[0] + xLength;
	rect.facadeTopRight[1] = startPoint[1] + yLength;
	rect.facadeTopRight[2] = startPoint[2] + zLength;

	return rect;
}

void draw(void) {
	cout << "draw" << endl;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluLookAt(0.1, 0.1, 10.0, 0.5, 0.5, 0.0, 2.0, 1.0, 0.0);
	Gl3DRect rect = create3DRectPoints(new GLfloat[3] { 0.0, 0.0, 0.0 }, 0.2,
			0.2, 0.2);
	rect.facadeColor[0] = 0.5f;
	rect.facadeColor[1] = 0.5f;
	rect.facadeColor[2] = 0.5f;
	draw3DRect(rect);
	glutSwapBuffers();
}

void init() {
	glViewport(0, 0, screenWidth, screenWidth);
}

void windowResize(int width, int height) {
	cout << "event{window resize:" << width << "x" << height << "}" << endl;
	glViewport(0, 0, width, height);
}

//--------main-----------
int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize the toolkit
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Set display mode
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidth) / 2,
			(glutGet(GLUT_SCREEN_HEIGHT) - screenHeight) / 2); // Set window pozition on screen
	glutInitWindowSize(screenWidth, screenHeight); // Set window size
	glutCreateWindow("My OpenGL Porgram"); // Open the screen window
	glutReshapeFunc(windowResize);
	glutDisplayFunc(draw); // Register redraw function
	init();
	glutMainLoop(); // Go into a perpetual loop
//������� dotPlot�����е�forѭ������һЩ���ľͿ��Ի���һ������ͼ��
}
