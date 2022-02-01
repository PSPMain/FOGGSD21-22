#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
	{
		GLUTCallbacks::Init(this);
		glutInit(&argc,argv);
		glutInitWindowSize(800,800);
		glutCreateWindow("Simple OpenGL Program");
		glutDisplayFunc(GLUTCallbacks::Display);
		glutMainLoop();
	}

void HelloGL::DrawPolygon()
{
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
		glColor4f(1.0f, 0.0f, 0.0f, 0.0);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.75, 0.5);
		glVertex2f(-0.75, -0.6);
		glEnd(); 
	}
}

void HelloGL::DrawIsocelesTriangle()
{
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
	glBegin(GL_POLYGON);//this starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);
		glEnd();
	}
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);//this clears the scene
	//DrawPolygon();
	//DrawScaleneTriangle();
	//DrawIsocelesTriangle();
	//DrawEqualateralTriangle();
	glFlush();//flushes the scene drawn to the graphics card
}

HelloGL::~HelloGL(void)
{

}

