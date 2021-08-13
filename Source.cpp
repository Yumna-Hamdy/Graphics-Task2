#include <stdlib.h>
#include <glut.h>
#include <math.h>

#define PI 3.14
static int shoulder = 0, elbow = 0, fingerBase = 0, fingerUp = 0, thumbUp=0, thumbBase=0;
int moving, startx, starty; int ztranslate = 0; int RIGHTLEG = 0; int RIGHTLEGSIDE = 0;
int RIGHTLEG2 = 0;  int LEFTLEG = 0; int LEFTLEGSIDE = 0;  int LEFTLEG2 = 0;
int elbow2 = 0; int shoulder2 = 0; int shouldery = 0; int shouldery1 = 0; int xtranslate = 0;
GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */
int ytranslate = 0;
double eye[] = { 0.0, 0.0, 5.0 };
double center[] = { 0.0, 0.0, 0.0 };
double up[] = { 0.0, 1.0, 0.0 };

/*void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}*/
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0,
		1.0,
		1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}
void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}
void lookRight()
{
	rotatePoint(up, PI / -8, eye);
}

void lookLeft()
{
	rotatePoint(up, PI / 8, eye);
}

void lookUp()
{
	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, PI / -8, eye);
	rotatePoint(horizontal, PI / -8, up);
}
void lookDown()
{
	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, PI / 8, eye);
	rotatePoint(horizontal, PI / 8, up);
}

void moveForward()
{
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	float speed = 0.1;
	eye[0] += direction[0] * speed;
	eye[1] += direction[1] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
}
void moveBackword()
{
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	float speed = -0.1;
	eye[0] += direction[0] * speed;
	eye[1] += direction[1] * speed;
	eye[2] += direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;
}
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		lookLeft();
		break;
	case GLUT_KEY_RIGHT:
		lookRight();
		break;
	case GLUT_KEY_UP:
		lookUp();
		break;
	case GLUT_KEY_DOWN:
		lookDown();
		break;
	}
	glutPostRedisplay();
}
void reset()
{
	double e[] = { 0.0, 0.0, 5.0 };
	double c[] = { 0.0, 0.0, 0.0 };
	double u[] = { 0.0, 1.0, 0.0 };
	for (int i = 0; i < 3; i++)
	{
		eye[i] = e[i];
		center[i] = c[i];
		up[i] = u[i];
	}
}

void display_arms(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glScalef(1, 1.3, 0.9);
	glTranslatef(0.0, 0.0, ztranslate);
	glTranslatef(xtranslate, 0.0, 0.0);
	glTranslatef(0.0, ytranslate, 0.0);
	glPushMatrix();
	glutWireCube(1.2);
	glScalef(0.5, 1, 0.4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.5, 0.0);
	glutWireSphere(0.3, 8.6, 8.6);
	

	glPopMatrix();
	/*first arm*/
	glPushMatrix();
	glTranslatef(0.6, 0.55, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.41, 0.0);
	glRotatef((GLfloat)shouldery1, 0.0, 1.0, 0.0);
	glTranslatef(-0.63, -0.22, 0.0);
	glPushMatrix();
	glTranslatef(0.55, 0.43, 0.0);
	glScalef(0.2, 0.5, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, 0.15, 0.0);
	glRotatef((GLfloat)elbow, 1.0, 0.0, 0.0);
	glTranslatef(1.55, -0.22, 0.0);
	glScalef(0.2, 0.5, 0.3);
	glutWireCube(1.0);
	glRotatef(-90, 0.0, 0.0, 1.0);
	glPopMatrix();
	glPopMatrix();
	/*glPushMatrix();

	glTranslatef(0.8, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.5, 0.6, 0.4);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glScalef(1.5, 0.6, 0.4);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();*/

	/*//Draw finger  1 
	//glPushMatrix();
	glPushMatrix();
	glTranslatef(1.0, -0.2, -0.45);
	glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();

	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	//Draw finger  2 
	glPushMatrix();
	glTranslatef(1.0, -0.2, -0.15);
	glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();

	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	//Draw finger  3 
	glPushMatrix();
	glTranslatef(1.0, -0.2, 0.150);
	glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	//Draw finger  4 
	glPushMatrix();
	glTranslatef(1.0, -0.2, 0.45);
	glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	//Draw finger thumb
	glPushMatrix();
	glTranslatef(1.0, 0.15, 0.45);
	glRotatef((GLfloat)thumbBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	

	
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)thumbUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();*/


	/*second arm*/

	/*glPushMatrix();

	glTranslatef(-2.8, 0.0, 0.0);
	glRotatef((GLfloat)shoulder2, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef(-180, 0.0, 0.0, 1.0);
	glPushMatrix();

	glScalef(1.5, 0.6, 0.4);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow2, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glScalef(1.5, 0.6, 0.4);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();*/
	/*first leg*/

	glPushMatrix();
	glTranslatef(-0.1, -0.8, 0.0);
	glRotatef((GLfloat)RIGHTLEG, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)RIGHTLEGSIDE, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.8, 0.0);
	glPushMatrix();
	glTranslatef(-0.25, -1.02, 0.0);
	glScalef(0.55, 0.7, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.8, -1.35, 0.0);
	glRotatef((GLfloat)RIGHTLEG2, 1.0, 0.0, 0.0);
	glTranslatef(-0.8, 1.35, 0.0);
	glPushMatrix();
	glTranslatef(-0.25, -1.72, 0.0);
	glScalef(0.55, 0.7, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.25, -2.0, 0.0);
	glScalef(0.55, 0.2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	/*second leg*/

	glPushMatrix();
	glTranslatef(0.1, -0.8, 0.0);
	glRotatef((GLfloat)LEFTLEG, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)LEFTLEGSIDE, 0.0, 0.0, 1.0);
	glTranslatef(-0.1, 0.8, 0.0);
	glPushMatrix();
	glTranslatef(0.25, -1.02, 0.0);
	glScalef(0.55, 0.7, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.8, -1.35, 0.0);
	glRotatef((GLfloat)LEFTLEG2, 1.0, 0.0, 0.0);
	glTranslatef(-0.8, 1.35, 0.0);
	glPushMatrix();
	glTranslatef(0.25, -1.72, 0.0);
	glScalef(0.55, 0.7, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.25, -2.0, 0.0);
	glScalef(0.55, 0.2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.6, 0.55, 0.0); 
	glRotatef((GLfloat)shoulder2, 0.0, 0.0, 1.0); 
	glTranslatef(0.0, -0.41, 0.0);  
	glRotatef((GLfloat)shouldery, 0.0, 1.0, 0.0); 
	glTranslatef(0.63, -0.22, 0.0);
	glPushMatrix();
	glTranslatef(-0.55, 0.43, 0.0);
	glScalef(0.2, 0.5, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0, 0.15, 0.0);
	glRotatef((GLfloat)elbow2, 1.0, 0.0, 0.0);
	glTranslatef(-1.55, -0.22, 0.0);
	glScalef(0.2, 0.5, 0.3);
	glutWireCube(1.0);
	glRotatef(-90, 0.0, 0.0, 1.0);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		up[0], up[1], up[2]);
	glutSwapBuffers();

}



void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		if (shoulder < 115)
		{
			shoulder = (shoulder + 5) % 360;
			glutPostRedisplay();
		}
		if (shoulder2 > -115)
		{
			shoulder2 = (shoulder2- 5) % 360;
			glutPostRedisplay();
		}
		break;
		glutPostRedisplay();
		break;
		
	case 'S':
		if (shoulder > 0)
		{
			shoulder = (shoulder - 5) % 360;
			glutPostRedisplay();
		}
		if (shoulder2 < 0)
		{
			shoulder2 = (shoulder2 + 5) % 360;
			glutPostRedisplay();
		}
		break;
		
		
	case 'e':
		if (elbow > -90)
		{
			elbow = (elbow - 5) % 360;
			glutPostRedisplay();
		}
		if (elbow2 > -90)
		{
			elbow2 = (elbow2 - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'E':
		if (elbow < 45)
		{
			elbow = (elbow + 5) % 360;
			glutPostRedisplay();
		}
		if (elbow2 < 45)
		{
			elbow2 = (elbow2 + 5) % 360;
			glutPostRedisplay();
		}
		break;
		
	case 'f':
		fingerBase = (fingerBase + 5);
		if (fingerBase  > 80)
		{
			fingerBase = (fingerBase - 5);
			//break;
		}

		glutPostRedisplay();
		//break;
		thumbBase = (thumbBase - 5);
		if (thumbBase == -80)
		{
			thumbBase = (thumbBase + 5);
			//break;
		}

		glutPostRedisplay();
		break;
	case 'F':
		fingerBase = (fingerBase - 5);
		if (fingerBase  == -80)
		{
			fingerBase = (fingerBase + 5);
			//break;
		}

		glutPostRedisplay();
		//break;
		thumbBase = (thumbBase + 5);
		if (thumbBase == 80)
		{
			thumbBase = (thumbBase - 5);
			//break;
		}

		glutPostRedisplay();
		break;

	case 'g':
		fingerUp = (fingerUp + 5) ;
		if (fingerUp > 95)
		{
			fingerUp = (fingerUp - 5) ;
			//break;
		}
		
		glutPostRedisplay();
		//break;
		thumbUp = (thumbUp - 5) ;
		if (thumbUp ==- 95)
		{
			thumbUp = (thumbUp +5);
			//break;
		}

		glutPostRedisplay();
		break;
	case 'G':
		fingerUp = (fingerUp - 5);
		if (fingerUp ==- 45)
		{
			fingerUp = (fingerUp + 5);
			//break;
		}

		glutPostRedisplay();
		//break;
		thumbUp = (thumbUp + 5);
		if (thumbUp == 45)
		{
			thumbUp = (thumbUp - 5);
			//break;
		}
	case 'l':
		
		if (RIGHTLEG> -90)
		{
			RIGHTLEG= (RIGHTLEG - 5) % 360; 
			glutPostRedisplay();
		}
		break;

	case 'L':
		if (LEFTLEG > -90)
		{
			LEFTLEG = (LEFTLEG - 5) % 360;
			glutPostRedisplay();
		}
		break;

	case 'n':
		if (RIGHTLEG < 65)
		{
			RIGHTLEG = (RIGHTLEG + 5) % 360;
			glutPostRedisplay();
		}
		break;

	case 'N':
		if (LEFTLEG < 65)
		{
			LEFTLEG = (LEFTLEG + 5) % 360;
			glutPostRedisplay();
		}
		break;

	case 'z': //move forward
		if (ztranslate > -5)
		{
			ztranslate = (ztranslate - 1) % 360;
			glutPostRedisplay();
		}
		break;
	case 'Z': //move backward
		if (ztranslate < 2)
		{
			ztranslate = (ztranslate + 1) % 360;
			glutPostRedisplay();
		}
		break;
	case 'x': //move forward
		if (xtranslate > -5)
		{
			xtranslate = (xtranslate - 1) % 360;
			glutPostRedisplay();
		}
		break;
	case 'X': //move backward
		if (xtranslate < 2)
		{
			xtranslate = (xtranslate + 1) % 360;
			glutPostRedisplay();
		}
		break;

	case 'y': //move forward
		if (ytranslate > -5)
		{
			ytranslate = (ytranslate - 1) % 360;
			glutPostRedisplay();
		}
		break;
	case 'Y': //move backward
		if (ytranslate < 2)
		{
			ytranslate = (ytranslate + 1) % 360;
			glutPostRedisplay();
		}
		break;

	case 'r':
		if (RIGHTLEG2 < 90)
		{
			RIGHTLEG2 = (RIGHTLEG2 + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'R':
		if (LEFTLEG2 < 90)
		{
			LEFTLEG2 = (LEFTLEG2 + 5) % 360;
			glutPostRedisplay();
		}
		break;

	case 't':
		if (RIGHTLEGSIDE < 10)
		{
			RIGHTLEGSIDE = (RIGHTLEGSIDE + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'T':
		if (RIGHTLEGSIDE > -85)
		{
			RIGHTLEGSIDE = (RIGHTLEGSIDE - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'm':
		if (LEFTLEGSIDE > -10)
		{
			LEFTLEGSIDE = (LEFTLEGSIDE - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'M':
		if (LEFTLEGSIDE < 85)
		{
			LEFTLEGSIDE = (LEFTLEGSIDE + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

static void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP) {
			moving = 0;
		}
	}
}


static void motion(int x, int y)
{
	if (moving) {
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	
	//glutDisplayFunc(display_right_arm);
	
	glutDisplayFunc(display_arms);
	
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
