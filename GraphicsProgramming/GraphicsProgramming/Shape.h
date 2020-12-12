
#pragma once

#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <Vector>

using namespace std;

class Shape
{

public:
	Shape();
	bool drawSquare();
	bool drawCube();
	bool drawSphere();
	bool drawPyramid();
	void render();

private:

	GLuint texture;
	float materialColour[4];
	bool isTransparent;

	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> textureCoords;
	vector<GLuint> indeces;



};


