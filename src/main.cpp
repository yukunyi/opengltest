// Draw the "dot plots" of a function
//P52 in <Computer Graphics Using OpenGL(Second Edition)>

#include<math.h>
#include<GL/glut.h>

const int screenWidth = 640; // width of screen window in pixels
const int screenHeight = 480; // height of screen window in pixels
GLdouble A, B, C, D; // values used for scaling and shifting

//----------Initialization--------------
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set white background color
	glColor3f(0.0f, 0.0f, 0.0f); // Drawing color is black
	glPointSize(2.0); // a 'dot' is 2 by 2 pixels
	glMatrixMode(GL_PROJECTION); // Set "camera shape"
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) screenWidth, 0.0, (GLdouble) screenHeight);
	// Set values used for scaling and shifting
	A = screenWidth / 4.0;
	B = 0.0;
	C = D = screenHeight / 2.0;

}

// --------Draw the "dot plots" of a function------
void dotPlots(void) {
	glClear(GL_COLOR_BUFFER_BIT); //clear the screen
	glBegin(GL_POINTS);
	for (GLdouble x = 0; x < 4.0; x += 0.005) {
		GLdouble func = exp(-x) * cos(2 * 3.14159265 * x);
		glVertex2d(A * x + B, C * func + D);
	}
	glEnd();
	// Draw a horizontal line
	glBegin(GL_LINES);
	glVertex2i(0, screenHeight / 2);
	glVertex2i(screenWidth, screenHeight / 2);
	glEnd();
	glFlush(); //send all output to display
}

//--------main-----------
int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize the toolkit
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Set display mode
	glutInitWindowPosition(100, 150); // Set window pozition on screen
	glutInitWindowSize(screenWidth, screenHeight); // Set window size
	glutCreateWindow("Dot plot of a Function"); // Open the screen window
	glutDisplayFunc(dotPlots); // Register redraw function
	init();
	glutMainLoop(); // Go into a perpetual loop
//在上面的 dotPlot（）中的for循环里做一些更改就可以画另一个函数图了
}
