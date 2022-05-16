#define _CRT_NO_WARNINGS

#include<Windows.h> // to get screen size
#include<bits/stdc++.h>
#include<glut.h>

using namespace std;

//_____________________
// Global Variables:
float screenWidth = GetSystemMetrics(SM_CXSCREEN);
float screenHeight = GetSystemMetrics(SM_CYSCREEN);
float timerScreenWidth, timerScreenHeight;
float r = 3, cx, cy;
float deltax,deltay;
float PI = 22 / 7.0;
bool isInFullScreen = true, circlecolor = true;
bool keyStates[256];  // for more than one input as [up + right , up + left, ... ]
//---------------------

void draw();
void timer(int);
void reshape(int, int);
void backGround();
void specialUp(int, int, int);
void specialDown(int, int, int);
void keyboardUp(unsigned char, int, int);
void keyboardDown(unsigned char, int, int);

int main(int argc, char** argv) {
	// glut initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // animation

	// create window
	glutCreateWindow("Keyboard Events");
	glutFullScreen();

	// call back functions
	glutDisplayFunc(draw); // to start drawing use glutDisplayFunc
	glutReshapeFunc(reshape);  // width, height
	glutTimerFunc(0, timer, 0);

	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);

	backGround();

	// main loop
	glutMainLoop();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glLineWidth(5);
	glColor3f(circlecolor, circlecolor, circlecolor);
	/*glBegin(GL_LINE_STRIP);
	for (float i = 0; i <= (2 * PI); i += (PI / 500))
		glVertex2f(cx + r * cos(i), cy + r * sin(i));
	glEnd();*/
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	for (float i = 0; i <= (2 * PI); i += (PI / 500))
		glVertex2f(cx + r * cos(i), cy + r * sin(i));
	glEnd();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	// view port  اطار الرؤية بتاعنا
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // to save my changes
	// glu: camera properties
	// coordinates
	if (not h)h = 1;
	float ratio = ceil(w * 1.0 / h);
	if (w >= h)gluOrtho2D(ceil(-10 * ratio), ceil(10 * ratio), -10, 10);
	else gluOrtho2D(-10, 10, ceil(-10 / ratio), ceil(10 / ratio));
	glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 25, timer, 0);
	cx = deltax;
	cy = deltay;
	qx -= 0.1;
	qy -= 0.1;
}

void backGround() {
	glClearColor(0.8f, 0.1f, 0.3f, 0);
}

void specialUp(int key, int x, int y) {
	keyStates[key] = false;
}
void specialDown(int key, int x, int y) {
	keyStates[key] = true;
	if(keyStates[GLUT_KEY_LEFT] and keyStates[GLUT_KEY_UP]){
		deltax -= 0.3;
		deltay += 0.3;
	}
	else if (keyStates[GLUT_KEY_LEFT] and keyStates[GLUT_KEY_DOWN]){
		deltax -= 0.3;
		deltay -= 0.3;
	}
	else if (keyStates[GLUT_KEY_RIGHT] and keyStates[GLUT_KEY_UP]){
		deltax += 0.3;
		deltay += 0.3;
	}
	else if (keyStates[GLUT_KEY_RIGHT] and keyStates[GLUT_KEY_DOWN]){
		deltax += 0.3;
		deltay -= 0.3;
	}
	else if (keyStates[GLUT_KEY_DOWN] and keyStates[GLUT_KEY_UP]) {
		deltay -= 0.3;
		deltay += 0.3;
	}
	else if (keyStates[GLUT_KEY_RIGHT] and keyStates[GLUT_KEY_LEFT]){
		deltax -= 0.3;
		deltax += 0.3;
	}
	else if (key == GLUT_KEY_LEFT)deltax -= 0.3;
	else if (key == GLUT_KEY_RIGHT)deltax += 0.3;
	else if (key == GLUT_KEY_UP)deltay += 0.3;
	else if (key == GLUT_KEY_DOWN)deltay -= 0.3;
	else if (key == GLUT_KEY_F1) {
		isInFullScreen = not isInFullScreen;
		if (isInFullScreen) {
			glutFullScreen();
		} else {
			glutReshapeWindow(screenWidth/2, screenHeight/2);
			glutPositionWindow(screenWidth / 4, screenHeight / 4);
		}
	}
}

void keyboardDown(unsigned char key, int x, int y) {
	keyStates[key] = true;
	if ((keyStates['a'] || keyStates['A']) && (keyStates['w'] || keyStates['W'])) {
		deltax -= 0.3;
		deltay += 0.3;
	}
	else if ((keyStates['a'] || keyStates['A']) && (keyStates['s'] || keyStates['S'])) {
		deltax -= 0.3;
		deltay -= 0.3;
	}
	else if ((keyStates['d'] || keyStates['D']) && (keyStates['w'] || keyStates['W'])) {
		deltax += 0.3;
		deltay += 0.3;
	}
	else if ((keyStates['d'] || keyStates['D']) && (keyStates['s'] || keyStates['S'])) {
		deltax += 0.3;
		deltay -= 0.3;
	}
	else if ((keyStates['d'] || keyStates['D']) && (keyStates['a'] || keyStates['A'])) {
		deltax -= 0.3;
		deltax += 0.3;
	}
	else if ((keyStates['w'] || keyStates['W']) && (keyStates['s'] || keyStates['S'])) {
		deltay -= 0.3;
		deltay += 0.3;
	}
	else if (tolower(key) == 'a')deltax -= 0.3;
	else if (tolower(key) == 'd')deltax += 0.3;
	else if (tolower(key) == 'w')deltay += 0.3;
	else if (tolower(key) == 's')deltay -= 0.3;
	else if (tolower(key) == 'q')circlecolor = !circlecolor;
	else if (key == 27)exit(0);
}

void keyboardUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

