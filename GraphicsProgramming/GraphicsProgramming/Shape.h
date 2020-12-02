
#pragma once

#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"

class Shape
{

public:
	Shape();
	bool drawSquare();
	bool drawCube();
	bool drawSphere();
	bool drawPyramid();

private:

	GLuint texture;
	float materialColour[4];
	bool isTransparent;


};


