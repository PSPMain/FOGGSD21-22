#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#define REFRESHRATE 16

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};



class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);
	void Display();
	void DrawPolygon();
	void DrawScaleneTriangle();
	void DrawIsocelesTriangle();
	void DrawEqualateralTriangle();
	void update();
	void Keyboard(unsigned char key, int x, int y);
private:
	float rotation;
	Camera* camera;
};

