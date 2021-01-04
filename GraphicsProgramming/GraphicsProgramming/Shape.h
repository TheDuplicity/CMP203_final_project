
#pragma once

#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <Vector>

using namespace std;


//set up defines to make it easy to select the shape to be created
#define SH_VERTEX  0x0001
#define SH_INDEX  0x0002
#define SH_CUBE  0x0003
#define SH_SQUARE  0x0004
#define SH_PYRAMID  0x0005
#define SH_SKYBOX  0x0006
#define SH_PLANE 0x0007


class Shape
{

public:
	// give the user the ability to change various aspects of the shape
	Shape();
	Shape(GLuint* inpTexture);
	bool setSquare();
	bool setCube();
	bool setSphere();
	bool setPyramid();
	bool setSkyBox();
	bool setPlane();
	void loadShape(int selectedShape);
	void render();
	void loadTexture(GLuint* shapeTexture) { texture = shapeTexture; };
	void loadColour(float r, float g, float b, float a);
	void setIsTransparent(bool inputTransparent) { isTransparent = inputTransparent; };
	void setIsTextured(bool inputTextured) { isTextured = inputTextured; };

private:

	//cariables to store what the shape is and where its textures etc are
	GLuint* texture;
	float materialColour[4];
	bool isTransparent;
	bool isTextured;
	int renderType;


	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> textureCoords;
	vector<GLuint> indeces;



};


