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
#include "SOIL.h"
#include <vector>
#include "Model.h"
#include "Camera.h"
#include "Shape.h"


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



	// predefined shapes
	Shape square;
	Shape skyBox;
	Shape example;

	// textures

	GLuint* defaultTexture;
	GLuint skyBoxTexture;
	GLuint secondTexture;

	// lighting

	GLfloat lightDiffuse[4]{ 0.5f,0.5f,0.5f,1.f };
	GLfloat lightAmbient[4]{ 0.f,0.f,0.f,0.f };
	GLfloat lightPosition[4]{ 0.f,0.f,0.f,1.f };
	GLfloat lightSpot[4]{};

	// models

	Model teapot;

	// camera

	Camera* cameraCurrent;
	Camera cameraPlayer1P;
	Camera secondCamera;
	GLfloat cameraSpeed;

	// materials

	GLfloat matDiffAndAmb[4]{ 1.f, 1.f, 1.f, 1.f };
	GLfloat matSpecular[4]{ 0.5f, 0.5f, 0.5f, 1.f };
	GLfloat matEmission[4]{ 0.5f, 0.5f, 0.5f, 1.f };
	GLfloat matNone[4]{ 0.f,0.f,0.f,0.f };
	GLint matShininess = 50;

	// random




	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

};

#endif