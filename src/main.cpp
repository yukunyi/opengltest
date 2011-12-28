// Draw the "dot plots" of a function
//P52 in <Computer Graphics Using OpenGL(Second Edition)>
#include<math.h>
#include<GL/glut.h>
#include<iostream>

using namespace std;

const int screenWidth = 640; // width of screen window in pixels
const int screenHeight = 480; // height of screen window in pixels

//视角
struct LookAt {
	GLfloat ex;
	GLfloat ey;
	GLfloat ez;
	GLfloat cx;
	GLfloat cy;
	GLfloat cz;
	GLfloat ux;
	GLfloat uy;
	GLfloat uz;
};

LookAt lookAt = { 0.3, 0.3, 0.3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };

//声明一个用于存放绘制6面体的结构体
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

	//绘制第一面（前面）
	glColor3f(rect.facadeColor[0], rect.facadeColor[1], rect.facadeColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.facadeTopLeft);
	glVertex3fv(rect.facadeTopRight);
	glVertex3fv(rect.facadeBottomRight);
	glVertex3fv(rect.facadeBottomLeft);
	glEnd();

	//绘制第二面（后面）
	glColor3f(rect.backFacadeColor[0], rect.backFacadeColor[1],
			rect.backFacadeColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.backFacadeTopLeft);
	glVertex3fv(rect.backFacadeTopRight);
	glVertex3fv(rect.backFacadeBottomRight);
	glVertex3fv(rect.backFacadeBottomLeft);
	glEnd();

	//绘制第三面（上面）
	glColor3f(rect.topColor[0], rect.topColor[1], rect.topColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.backFacadeTopLeft);
	glVertex3fv(rect.backFacadeTopRight);
	glVertex3fv(rect.facadeTopRight);
	glVertex3fv(rect.facadeTopLeft);
	glEnd();

	//绘制第四面（下面）
	glColor3f(rect.bottomColor[0], rect.bottomColor[1], rect.bottomColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.backFacadeBottomLeft);
	glVertex3fv(rect.backFacadeBottomRight);
	glVertex3fv(rect.facadeBottomRight);
	glVertex3fv(rect.facadeBottomLeft);
	glEnd();

	//绘制第五面（左面）
	glColor3f(rect.leftColor[0], rect.leftColor[1], rect.leftColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.facadeTopLeft);
	glVertex3fv(rect.facadeBottomLeft);
	glVertex3fv(rect.backFacadeBottomLeft);
	glVertex3fv(rect.backFacadeTopLeft);
	glEnd();

	//绘制第六面（右面）
	glColor3f(rect.rightColor[0], rect.rightColor[1], rect.rightColor[2]);
	glBegin(GL_POLYGON);
	glVertex3fv(rect.facadeTopRight);
	glVertex3fv(rect.facadeBottomRight);
	glVertex3fv(rect.backFacadeBottomRight);
	glVertex3fv(rect.backFacadeTopRight);
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

void drawPointRect(GLfloat color[]) {
	glColor3fv(color);
	glBegin(GL_LINES);
	glVertex3fv((GLfloat[]) {-100.0, 0.0, 0.0});
	glVertex3fv((GLfloat[]) {100.0, 0.0, 0.0});
	glEnd();
	glBegin(GL_LINES);
	glVertex3fv((GLfloat[]) {0.0, -100.0, 0.0});
	glVertex3fv((GLfloat[]) {0.0, 100.0, 0.0});
	glEnd();
	glBegin(GL_LINES);
	glVertex3fv((GLfloat[]) {0.0, 0.0, -100.0});
	glVertex3fv((GLfloat[]) {0.0, 0.0, 100.0});
	glEnd();

}

void draw(void) {
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	gluPerspective(0.0, 1.0, 0.0, 1.0);
	gluLookAt(lookAt.ex, lookAt.ey, lookAt.ez, lookAt.cx, lookAt.cy, lookAt.cz,
			lookAt.ux, lookAt.uy, lookAt.uz);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat startPoints[] = { -0.1, -0.1, -0.1 };
	Gl3DRect rect = create3DRectPoints(startPoints, 0.2, 0.2, 0.2);
	rect.facadeColor[0] = 1.0f;
	rect.facadeColor[1] = 1.0f;
	rect.facadeColor[2] = 1.0f;

	rect.backFacadeColor[0] = 1.0f;
	rect.backFacadeColor[1] = 1.0f;
	rect.backFacadeColor[2] = 1.0f;

	rect.leftColor[0] = 0.1f;
	rect.leftColor[1] = 0.9f;
	rect.leftColor[2] = 0.56f;

	rect.rightColor[0] = 0.1f;
	rect.rightColor[1] = 0.9f;
	rect.rightColor[2] = 0.56f;

	rect.topColor[0] = 0.1f;
	rect.topColor[1] = 0.2f;
	rect.topColor[2] = 0.56f;

	rect.bottomColor[0] = 0.1f;
	rect.bottomColor[1] = 0.2f;
	rect.bottomColor[2] = 0.56f;
	draw3DRect(rect);
	drawPointRect((GLfloat[]) {0.3,0.3,0.3});
	glutSwapBuffers();
//	glFlush();
}

void windowResize(int width, int height) {
	glViewport(0, 0, width, height);
}

void keyPressed(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		lookAt.ex = lookAt.ex - 0.01;
	} else if (key == GLUT_KEY_RIGHT) {
		lookAt.ex = lookAt.ex + 0.01;
	} else if (key == GLUT_KEY_UP) {
		lookAt.ey = lookAt.ey + 0.01;
	} else if (key == GLUT_KEY_DOWN) {
		lookAt.ey = lookAt.ey - 0.01;
	} else if (key == GLUT_KEY_F1) {
		lookAt.ez = lookAt.ez - 0.01;
	} else if (key == GLUT_KEY_F2) {
		lookAt.ez = lookAt.ez + 0.01;
	}
	cout << "lookAt{" << lookAt.ex << "," << lookAt.ey << "," << lookAt.ez
			<< "}" << endl;
	glutPostRedisplay();
}

void init() {
	glEnable(GL_DEPTH_TEST);
	// Uncomment out the first block of code below, and then the second block,
	//  to see how they affect line and point drawing.

	// The following commands should cause points and line to be drawn larger
	// than a single pixel width.
	glPointSize(8);
	glLineWidth(5);

	// The following commands should induce OpenGL to create round points and
	// antialias points and lines.  (This is implementation dependent unfortunately).
	//RGBA mode antialias need cooperate with blend function.
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Antialias the lines
	glHint(GL_POLYGON_SMOOTH, GL_NICEST); // Antialias the lines
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//--------main-----------
int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidth) / 2,
			(glutGet(GLUT_SCREEN_HEIGHT) - screenHeight) / 2); // Set window pozition on screen
	glutInitWindowSize(screenWidth, screenHeight); // Set window size
	glutCreateWindow("My OpenGL Porgram"); // Open the screen window
	glutSpecialFunc(keyPressed);
	glutReshapeFunc(windowResize);
	glutDisplayFunc(draw); // Register redraw function
	init();
	glutMainLoop(); // Go into a perpetual loop
}
