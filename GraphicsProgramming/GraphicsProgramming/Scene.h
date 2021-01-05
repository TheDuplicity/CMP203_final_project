// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "time.h"
#include "SOIL.h"
#include <vector>
#include "Model.h"
#include "Camera.h"
#include "Shape.h"
#include "Shadow.h"
#include "Light.h"


class Scene {

public:
	Scene(Input* in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();


	// draw primitive variables?

	void drawMirrorWorld();
	void renderScene();
	void renderShadows();
	void userInputCamera(float dt);
	void userInputLight(float dt);
	void renderTableObjects();

	//shadows
	Shadow shadow;

	// predefined shapes
	Shape square;
	Shape skyBox;
	Shape floor;
	Shape light;
	Shape mirror;
	Shape ceiling;
	Shape shapeChanger;
	int newShape;
	float swapShapeTimer;
	Shape wall;

	// textures

	GLuint* defaultTexture;
	GLuint skyBoxTexture;
	GLuint secondTexture;
	GLuint floorTexture;
	GLuint ceilingTexture;
	GLuint mirrorTexture;
	GLuint wallTexture;
	
	// Lights

	Light mainLight;
	Light colouredLight;
	Light flashingLight;
	Light flashLight;
	Light* currentLight;


	GLfloat lightDiffuse[4]{ 0.7f,0.4f,0.4f,1.f };
	GLfloat lightAmbient[4]{ 0.f,0.f,0.f,0.f };
	GLfloat lightPosition[4]{ 3.f,3.f,0.f,1.f };
	GLfloat lightSpot[4]{};

	// models

	Model teapot;
	Model table;
	Model sword;
	Model flashLightModel;

	// camera
	
	Camera* cameraCurrent;
	Camera cameraPlayer1P;
	Camera cameraPlayer3P;
	Camera swordCamera;
	GLfloat cameraSpeed;

	// materials

	GLfloat matDiffAndAmb[4]{ 1.f, 1.f, 1.f, 1.f };
	GLfloat matSpecular[4]{ 0.5f, 0.5f, 0.5f, 1.f };
	GLfloat matEmission[4]{ 0.5f, 0.5f, 0.5f, 1.f };
	GLfloat matNone[4]{ 0.f,0.f,0.f,0.f };
	GLint matShininess = 50;

	// random

	float colouredLightLimitsMax;
	float colouredLightLimitsMin;
	float colouredLightVelocity;
	bool tableSpin;
	float tableSpinSpeed;
	float colourChangeTimer;
	float tempRotate;
	Vector3 mirrorPosition = (5.0,0.0,0.0);
	int shadowCheck;
	int userInputSelect;
	GLfloat swordRotation;
	GLfloat swordOrbit;
	bool swordCameraFixed;

	GLfloat floorCorners[12] = {
		-25, -3, 25,
		25, -3, 25,
		25, -3, -25,
		-25, -3, -25
	};
	GLfloat ceilingCorners[12] = {
		-25, 5, 25,
		25, 5, 25,
		25, 5, -25,
		-25, 5, -25
	};

	GLfloat shadowMatrix[16];

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, timefps, timebase = 0;
	char fps[40];
	char mouseText[40];

};

#endif