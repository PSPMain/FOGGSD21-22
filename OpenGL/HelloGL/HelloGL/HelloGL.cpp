#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
	{
		camera = new Camera();
		camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
		camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
		camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
		rotation = 0.0f;
		GLUTCallbacks::Init(this);
		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE);
		glutInitWindowSize(800,800);
		glutInitWindowPosition(500, 100);
		glutCreateWindow("Simple OpenGL Program");
		glutDisplayFunc(GLUTCallbacks::Display);
		glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
		glutKeyboardFunc(GLUTCallbacks::Keyboard);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, 800, 800);
		gluPerspective(45, 1, 0, 100);
		glMatrixMode(GL_MODELVIEW);
		glutMainLoop();
	}

void HelloGL::DrawPolygon()
{
	glPushMatrix();
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);//this starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.75, 0.5);//this defines the first point of the polygon, top left
		glVertex2f(0.75, 0.5);//next point, top right
		glVertex2f(0.75, -0.5);//bottom right
		glVertex2f(-0.75, -0.5);//last point of the polygon, bottom left
		glEnd();//defines the end of the draw
	}
}

void HelloGL :: DrawScaleneTriangle()
{
	glBegin(GL_POLYGON);//this starts to draw a polygon
	{
		glPushMatrix();
		glRotatef(rotation, 0.0f, 0.0f, -1.0f);
		glColor4f(1.0f, 0.0f, 0.0f, 0.0);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.75, 0.5);
		glVertex2f(-0.75, -0.6);
		glEnd(); 
	}
}

void HelloGL::DrawIsocelesTriangle()
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	glBegin(GL_POLYGON);//this starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0);
		glVertex2f(0.0, 0.6);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);
		glEnd();
	}
}

void HelloGL::DrawEqualateralTriangle()
{	
	glPushMatrix();
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);//this starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);
		glEnd();
	}
}

void HelloGL::update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glTranslatef(0.0f, 0.0f, -5.0f);
	if (rotation >= 360.0f)
	{
		rotation = 0.0f;
	}
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
	{
		rotation += 0.5f;
	}
	else if (key == 'a')
	{
		rotation -= 0.5f;
	}
	else if (key == 'up')
	{
		
	}
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);//this clears the scene
	/*DrawPolygon();*/
	//DrawScaleneTriangle();
	//DrawIsocelesTriangle();
	//DrawEqualateralTriangle();
	glPushMatrix();
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
	glutWireTeapot(1);
	glPopMatrix();
	glFlush();//flushes the scene drawn to the graphics card
	glutSwapBuffers();
}


HelloGL::~HelloGL(void)
{

}

