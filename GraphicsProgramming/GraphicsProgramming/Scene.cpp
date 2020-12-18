#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.

		// DEPTH TESTING

	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//stencil stuff

	glShadeModel(GL_SMOOTH);
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);
	glClearDepth(1.0f);
	glClearStencil(0);
	glEdgeFlag(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// lighting

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.2);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0f);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightSpot);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 50.0);

	//materials

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matDiffAndAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

	// textures

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	skyBoxTexture = SOIL_load_OGL_texture
	(
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	defaultTexture = &skyBoxTexture;
	// Initialise scene variables
	teapot.load("models/teapot.obj","gfx/crate.png");
	cameraCurrent = &cameraPlayer1P;
	cameraSpeed = 2;
	glutSetCursor(GLUT_CURSOR_NONE);
	cameraCurrent->update();
}



void Scene::handleInput(float dt)
{


	// Handle user input

	//rotation pitch(x) yaw(y) roll(z)
	if (input->getMouseX() > (width/2.0) || input->getMouseX() < (width / 2.0)) {
		cameraCurrent->setYaw(cameraCurrent->getYaw() + ((input->getMouseX() - (width / 2.0 ))*dt * cameraCurrent->getRotSpeed().x));
		cameraCurrent->update();
	}
	if (input->getMouseY() > (height / 2.0) || input->getMouseY() < (height / 2.0)) {

		cameraCurrent->setPitch(cameraCurrent->getPitch() - ((input->getMouseY() - (height / 2.0)) * dt * cameraCurrent->getRotSpeed().y));
		cameraCurrent->update();
	}
	if (input->isKeyDown('r')) {
		cameraCurrent->setRoll(cameraCurrent->getRoll() + 90 * dt);
		cameraCurrent->update();
	}
	//forward backwards
	if (input->isKeyDown('w')) {
		cameraCurrent->setPosition(cameraCurrent->getPosition() + Vector3(cameraSpeed * dt * cameraCurrent->getForward().x, 0/*cameraSpeed * dt * cameraCurrent->getForward().y*/, cameraSpeed * dt * cameraCurrent->getForward().z));
		cameraCurrent->update();
	}

	if (input->isKeyDown('s')) {
		cameraCurrent->setPosition(cameraCurrent->getPosition() - Vector3(cameraSpeed * dt * cameraCurrent->getForward().x, 0/*cameraSpeed * dt * cameraCurrent->getForward().y*/, cameraSpeed * dt * cameraCurrent->getForward().z));
		cameraCurrent->update();
	}
	// left right
	if (input->isKeyDown('a')) {
		cameraCurrent->setPosition(cameraCurrent->getPosition() - Vector3(cameraSpeed * dt * cameraCurrent->getRight().x, 0/*cameraSpeed * dt * cameraCurrent->getRight().y*/, cameraSpeed * dt * cameraCurrent->getRight().z));
		cameraCurrent->update();
	}

	if (input->isKeyDown('d')) {
		cameraCurrent->setPosition(cameraCurrent->getPosition() + Vector3(cameraSpeed * dt * cameraCurrent->getRight().x, 0/*cameraSpeed * dt * cameraCurrent->getRight().y*/, cameraSpeed * dt * cameraCurrent->getRight().z));
		cameraCurrent->update();
	}
	//up down
	if (input->isKeyDown(32)) {
		cameraCurrent->setPosition(cameraCurrent->getPosition() + Vector3(0/*cameraSpeed * dt * cameraCurrent->getUp().x*/, cameraSpeed * dt * cameraCurrent->getUp().y, 0/* cameraSpeed * dt * cameraCurrent->getUp().z*/));
		cameraCurrent->update();
	}
	if (input->isKeyDown('e')) {
		cameraCurrent->setPosition(cameraCurrent->getPosition() - Vector3(0/*cameraSpeed * dt * cameraCurrent->getUp().x*/, cameraSpeed * dt * cameraCurrent->getUp().y, 0/*cameraSpeed * dt * cameraCurrent->getUp().z*/));
		cameraCurrent->update();
	}

	glutWarpPointer(width / 2.0, height / 2.0);
}

void Scene::update(float dt)
{
	// update scene related variables.
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	//gluLookAt(0,0,0,0,6,0,0,1,0);
	gluLookAt(cameraCurrent->getPosition().x, cameraCurrent->getPosition().y, cameraCurrent->getPosition().z,
		cameraCurrent->getLookAt().x, cameraCurrent->getLookAt().y, cameraCurrent->getLookAt().z,
		cameraCurrent->getUp().x, cameraCurrent->getUp().y, cameraCurrent->getUp().z);
	
	// Render geometry/scene here -------------------------------------

	//skybox
	glPushMatrix();
	defaultTexture = &skyBoxTexture;
	glDisable(GL_DEPTH_TEST);
	glTranslatef(cameraCurrent->getPosition().x, cameraCurrent->getPosition().y, cameraCurrent->getPosition().z);
	skyBox.render();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, *defaultTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glPushMatrix();
	glTranslatef(2.5,0,0);
	glScalef(0.1,0.1,0.1);
	teapot.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
	glScalef(0.1,0.1,0.1);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0, 1);
	glVertex3f(-0.5, -0.5, 0);
	glNormal3f(0, 0, 1);

	glTexCoord2d(1, 1);
	glVertex3f(0.5, -0.5, 0);
	glNormal3f(0, 0, 1);

	glTexCoord2d(0, 0);
	glVertex3f(-0.5, 0.5, 0);
	glNormal3f(0, 0, 1);

	glTexCoord2d(1, 0);
	glVertex3f(0.5, 0.5, 0);
	glNormal3f(0, 0, 1);
	glEnd();
	glPopMatrix();

	//glTranslatef(transl[1], transl[0], transl[2]);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0, 1);
	glVertex3f(-0.5, -0.5, 0);
	glNormal3f(0, 0, 1);

	glTexCoord2d(1, 1);
	glVertex3f(0.5, -0.5, 0);
	glNormal3f(0, 0, 1);

	glTexCoord2d(0, 0);
	glVertex3f(-0.5, 0.5, 0);
	glNormal3f(0, 0, 1);

	glTexCoord2d(1, 0);
	glVertex3f(0.5, 0.5, 0);
	glNormal3f(0, 0, 1);
	glEnd();
	
	/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &verts[0]);
	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

		
		glBegin(GL_TRIANGLE_STRIP);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);
		glEnd();
		
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, index);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	*/

	glTranslatef(0,2,0);
	square.render();


	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
