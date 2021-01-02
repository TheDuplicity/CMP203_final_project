#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.

	// set mipmap linear for anti aliasing

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// wireframe and fill modes

	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_BACK, GL_LINE);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

		// DEPTH TESTING
	
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//to ensure stencil is working properly

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


	//materials

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matDiffAndAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

	// textures

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	wallTexture = SOIL_load_OGL_texture
	(
		"gfx/wallTexture.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	skyBoxTexture = SOIL_load_OGL_texture
	(
		"gfx/skyBoxTexture.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	secondTexture = SOIL_load_OGL_texture
	(
		"gfx/bluered.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	ceilingTexture = SOIL_load_OGL_texture
	(
		"gfx/floorTexture.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	floorTexture = SOIL_load_OGL_texture
	(
		"gfx/grass.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	mirrorTexture = SOIL_load_OGL_texture
	(
		"gfx/mirrorTexture.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	defaultTexture = &skyBoxTexture;
	// Initialise scene variables

	glutSetCursor(GLUT_CURSOR_NONE);
	tempRotate = 0;
	swordRotation = 0;
	swordOrbit = 0;

	mirrorPosition.x = 5.0;
	mirrorPosition.y = 2.0;
	shadowCheck = 0;
	userInputSelect = 1;

	newShape = 1;
	swapShapeTimer = 0;

	//cameras

	cameraCurrent = &cameraPlayer1P;
	cameraSpeed = 10;
	cameraCurrent->update();
	cameraPlayer1P.setPosition(Vector3(cameraPlayer1P.getPosition().x, cameraPlayer1P.getPosition().y + 5, cameraPlayer1P.getPosition().x));
	swordCamera.setPosition(Vector3(-20, 8, -3));
	swordCamera.update();
	swordCameraFixed = false;

	cameraPlayer1P.update();
	cameraPlayer3P.update();

	//models
	table.load("models/table.obj", "models/Wood_Table_C.jpg");
	teapot.load("models/teapot.obj", "gfx/floorTexture.png");
	sword.load("models/sword.obj", "models/Sting_Base_Color.png");
	flashLightModel.load("models/flashLight.obj", "gfx/mirrorTexture.png");

	//sort out shapes

	square.loadTexture(&skyBoxTexture);
	square.loadShape(SH_SKYBOX);
	square.loadColour(1, 1, 1, 1);
	square.setIsTransparent(true);
	skyBox.loadTexture(&skyBoxTexture);
	skyBox.loadShape(SH_SKYBOX);
	floor.loadTexture(&floorTexture);
	floor.loadShape(SH_PLANE);
	ceiling.loadTexture(&ceilingTexture);
	ceiling.loadShape(SH_PLANE);
	mirror.loadShape(SH_SQUARE);
	mirror.loadTexture(&mirrorTexture);
	mirror.loadColour(0.3, 0.3, 0.85, 0.65);
	mirror.setIsTransparent(true);
	mirror.setIsTextured(true);
	shapeChanger.loadColour(0.5, 0.5, 0.5, 1.f);
	shapeChanger.loadShape(SH_SQUARE);
	shapeChanger.setIsTextured(false);
	wall.loadTexture(&wallTexture);
	wall.loadShape(SH_PLANE);
	wall.setIsTextured(true);

	//lights
	mainLight.setLightPosition(new GLfloat[4]{ 0,0,0,1 });
	mainLight.setLightAmbient(new GLfloat[4]{ 1,1,1,1 });
	mainLight.setLightDiffuse(new GLfloat[4]{ 0.1,0.1,0.1,1 });
	mainLight.setConstantAttenuation(0);
	mainLight.setLinearAttenuation(0);
	mainLight.setQuadraticAttenuation(0);
	mainLight.setUpLightBulb(&ceilingTexture, SH_CUBE, new GLfloat[4]{1,1,1,1}, false, true);
	mainLight.setThisLight(GL_LIGHT0);
	//mainLight.applyLightParameters(false);

	mainLight.setLightAmbient(new GLfloat[4]{ 0,0,0,1 });
	flashLight.setLightPosition(new GLfloat[4]{ 0,0,-14,1.f });
	flashLight.setLightDiffuse(new GLfloat[4]{ 1,1,1,1.f });
	flashLight.setLightSpot(new GLfloat[3]{ 0.f,0.f,-1.f});
	flashLight.setConstantAttenuation(0.3);
	flashLight.setLinearAttenuation(0.1);
	flashLight.setQuadraticAttenuation(0);
	flashLight.setUpLightBulb(&ceilingTexture, SH_CUBE, new GLfloat[4]{ 1,1,1,1 }, false, true);
	flashLight.setThisLight(GL_LIGHT1);
	flashLight.applyLightParameters(true);

	//
	//
	//
	//
	//
	//TO DO
	/*
	user created geometry
		lightingand texturing
		transparencyand depth sorting
		procedurally generated shapes / primitives which are correctly lit and textured
		use of vertex arrays
		multiple lights of different colours and some animated
		some user controllable lights
		working camera using mouseand keyboard controls
		multiple cameras with different comtrol schemes like procedurally cxontrolled vies, 3rd person, limited controls, tracking
		control ovjects in the scene other than the camera
		hierarchichal modeling like the solar system example
		use of shadowsand the stencil buffer
		a wireframe mode
		well commentedand use of classes
	* 
	* 
	* 
	* 
	get a flashlight obj modeland have it shine a light at a wall
		make a light that changes coloursand moves around the player like a fairyand give it a sphere object
		make another light that changes brightness(let the player move this)
		make a couple spheres cuz why not
		*/
	//
		//
		//
		//
		//
		//
		//

	/*
	mainLight.setLightPosition(new GLfloat[4]{ 0,0,0,1 });
	mainLight.setLightAmbient(new GLfloat[4]{ 1,1,1,1 });
	mainLight.setLightDiffuse(new GLfloat[4]{ 0.1,0.1,0.1,1 });
	mainLight.setConstantAttenuation(0.1);
	mainLight.setLinearAttenuation(0.1);
	mainLight.setQuadraticAttenuation(0.1);
	mainLight.setUpLightBulb(&ceilingTexture, SH_CUBE, new GLfloat[4]{ 1,1,1,1 }, false, true);
	mainLight.setThisLight(GL_LIGHT0);
	mainLight.applyLightParameters(false);

	mainLight.setLightPosition(new GLfloat[4]{ 0,0,0,1 });
	mainLight.setLightAmbient(new GLfloat[4]{ 1,1,1,1 });
	mainLight.setLightDiffuse(new GLfloat[4]{ 0.1,0.1,0.1,1 });
	mainLight.setConstantAttenuation(0.1);
	mainLight.setLinearAttenuation(0.1);
	mainLight.setQuadraticAttenuation(0.1);
	mainLight.setUpLightBulb(&ceilingTexture, SH_CUBE, new GLfloat[4]{ 1,1,1,1 }, false, true);
	mainLight.setThisLight(GL_LIGHT0);
	mainLight.applyLightParameters(false);
	*/

	currentLight = &flashLight;
	
}

void Scene::renderShadows() {
	shadowCheck = 1;
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(mainLight.getLightDiffuse()[0] / 5.0, mainLight.getLightDiffuse()[1] / 5.0, mainLight.getLightDiffuse()[2] / 5.0, .4f);
	glTranslatef(0,0.1,0);
	shadow.generateShadowMatrix(shadowMatrix, mainLight.getLightPosition(), floorCorners);
	glMultMatrixf((GLfloat*)shadowMatrix);
	renderScene();

	//render the mirrors shadow too
	glPushMatrix();
	glTranslatef(mirrorPosition.x, mirrorPosition.y, mirrorPosition.z);
	glScalef(10, 7, 14);
	glRotatef(-90, 0, 1, 0);
	mirror.render();
	glPopMatrix();

	glColor4f(1.0f, 1.0f, 1.0f,1.f);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);

	glPopMatrix();
	shadowCheck = 0;
}

void Scene::renderTableObjects() {
	glPushMatrix();

	//render table
	glPushMatrix();
	glScalef(15, 10, 15);
	table.render();
	glPopMatrix();


	glPushMatrix();
	// move to the top of the table
	//render the changing shape
	glTranslatef(0, 5.5, 0);
	glPushMatrix();
	glTranslatef(3,0,-1);
	if (swapShapeTimer > 0.25f) {
		swapShapeTimer = 0;
		newShape++;
	}
	if (newShape > 6 || newShape < 3) {
			newShape = 3;
	}
	
	shapeChanger.loadShape(newShape);
	shapeChanger.render();
	glPopMatrix();

	// render teapot on top of the table
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glRotatef(tempRotate, 0, 1, 0);
	teapot.render();
	glPopMatrix();

	glPopMatrix();

	//render spinning sword
	glPushMatrix();
	glRotatef(swordOrbit, 0, 1, 0);
	glTranslatef(10, 3, 0);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(swordRotation, 0, 1, 0);
	sword.render();
	glPopMatrix();

	glPopMatrix();
}

void Scene::renderScene() {
	//rendingwall and flashLightModel and light together
	glPushMatrix();
	glTranslatef(0,0,-12);

	//render the flashLightModel
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glScalef(0.1,0.1,0.1);
	flashLightModel.render();
	glPopMatrix();

	//render the wall
	glPushMatrix();
	glTranslatef(0,0,-5);
	glRotatef(90,1,0,0);
	glScalef(0.3,0.3,0.3);
	wall.render();
	glPopMatrix();
	//render the light if shadows arent being rendered
	if (shadowCheck == 0) {


	}

	glPopMatrix();

	glPushMatrix();
	//glScalef(10, 10, 10);
	flashLight.render();
	glPopMatrix();

	// cube is rendered seperately from the rest of the scene
	glPushMatrix();
	glTranslatef(0, 2, 0);
	square.render();
	glPopMatrix();

	// table and the objects on it are rendered using hierarchical modelling and a miniature version is rendered on the tabletop
	glPushMatrix();
	glTranslatef(-10, -3, 0);
	renderTableObjects();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13, 2, 0);
	glScalef(0.1,0.1,0.1);
	renderTableObjects();
	glPopMatrix();

	// these objects will not be drawn if shadows are being created
	if (shadowCheck == 0) {
		//rendering the lights
		mainLight.render();

		//rendering the floor and ceiling
		glPushMatrix();
		glTranslatef(0, -3, 0);
		glScalef(5, 5, 5);
		floor.render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 14, 0);
		glScalef(5, 5, 5);
		ceiling.render();
		glPopMatrix();
	}

	

}

void Scene::drawMirrorWorld() {
	// setup stencil
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);

	//draw the stencil
	glPushMatrix();
	glTranslatef(mirrorPosition.x, mirrorPosition.y, mirrorPosition.z);
	glScalef(10, 7, 14);
	glRotatef(-90, 0, 1, 0);
	mirror.render();
	glPopMatrix();

	//set everything back to normal except the stencil so the next objects will be written in the stencil world
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);


	//translate double the distance of the mirror to the origin to have the scene drawn on the opposite side then draw the scene
	glPushMatrix();
	glTranslatef(mirrorPosition.x * 2.0, 0, 0);
	glScalef(-1, 1, 1);
	renderScene();
	renderShadows();
	glPopMatrix();

	glDisable(GL_STENCIL_TEST);
}

void Scene::userInputCamera(float dt) {
	if (dt > 1) {
		dt = 0;
	}
	//rotation pitch(x) yaw(y) roll(z)
	if (input->getMouseX() > (width / 2.0) || input->getMouseX() < (width / 2.0)) {
		cameraCurrent->setYaw(cameraCurrent->getYaw() + ((input->getMouseX() - (width / 2.0)) * dt * cameraCurrent->getRotSpeed().x));
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

}
void Scene::userInputLight(float dt) {
	if (dt > 1) {
		dt = 0;
	}
	if (input->isKeyDown('w')) {
		currentLight->getLightPosition()[1] += 3 * dt;
	}
	if (input->isKeyDown('s')) {
		currentLight->getLightPosition()[1] -= 3 * dt;
	}
	if (input->isKeyDown('d')) {
		currentLight->getLightPosition()[0] += 3 * dt;
	}
	if (input->isKeyDown('a')) {
		currentLight->getLightPosition()[0] -= 3 * dt;
	}
	if (input->isKeyDown('q')) {
		currentLight->getLightPosition()[2] += 3 * dt;
	}
	if (input->isKeyDown('e')) {
		currentLight->getLightPosition()[2] -= 3 * dt;
	}

}

void Scene::handleInput(float dt)
{
	if (dt > 1) {
		dt = 0;
	}
	switch (userInputSelect)
	{
		case 1:
			userInputCamera(dt);
			break;
		case 2:
			userInputLight(dt);
			break;
	default:
		break;
	}

	// Handle user input

	if (input->isKeyDown('c')) {
		if (input->isKeyDown('1')) {
			cameraCurrent = &cameraPlayer1P;
		}
		else if (input->isKeyDown('2')) {
			cameraCurrent = &cameraPlayer3P;
		}
		else if (input->isKeyDown('3')) {
			cameraCurrent = &swordCamera;
		}
	}
	else if (input->isKeyDown('l')) {	
		if (input->isKeyDown('1')) {
			currentLight = &mainLight;
		}
		else if (input->isKeyDown('2')) {
			currentLight = &colouredLight;
		}
		else if (input->isKeyDown('3')) {
			currentLight = &flashingLight;
		}		
	}
	else {
		if (input->isKeyDown('1')) {
			userInputSelect = 1;
		}
		else if (input->isKeyDown('2')) {
			userInputSelect = 2;
		}
		else if (input->isKeyDown('3')) {
			userInputSelect = 3;
		}
	}

	if (input->isKeyDown('-')) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);

	}
	else if (input->isKeyDown('=')) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}

	glutWarpPointer(width / 2.0, height / 2.0);
}

void Scene::update(float dt)
{
	if (dt > 1) {
		dt = 0;
	}
	swapShapeTimer += dt;
	// update scene related variables.
	// Calculate FPS for output
	tempRotate += 90 * dt;
	swordRotation += 270 * dt;
	swordOrbit += -90 * dt;
	if (swordRotation >= 360) {
		swordRotation = 0;
	}
	if (swordOrbit >= 360) {
		swordOrbit = 0;
	}
	swordCamera.setYaw(swordOrbit);
	if (cameraCurrent == &swordCamera) {
		
		swordCamera.update();
		swordCamera.setLookAt(Vector3(-10, 4,0));
		if (!swordCameraFixed) {
			swordCameraFixed = true;
		}
	}
	if (swordCameraFixed) {
		swordCamera.setPosition(swordCamera.getPosition() + Vector3(
			swordCamera.getForward().x * (90.f / 360.f) * (2 * 3.14159 * 10) * dt,
			swordCamera.getForward().y * (90.f / 360.f) * (2 * 3.14159 * 10) * dt,
			swordCamera.getForward().z * (90.f / 360.f) * (2 * 3.14159 * 10) * dt
		));
	}
	
	
	calculateFPS();
}

void Scene::render() {
	
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	//gluLookAt(0,0,0,0,6,0,0,1,0);
	gluLookAt(cameraCurrent->getPosition().x, cameraCurrent->getPosition().y, cameraCurrent->getPosition().z,
		cameraCurrent->getLookAt().x, cameraCurrent->getLookAt().y, cameraCurrent->getLookAt().z,
		cameraCurrent->getUp().x, cameraCurrent->getUp().y, cameraCurrent->getUp().z);
	
	// Render geometry/scene here -------------------------------------

	glBindTexture(GL_TEXTURE_2D, *defaultTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matDiffAndAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

		//skybox
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	glTranslatef(cameraCurrent->getPosition().x, cameraCurrent->getPosition().y, cameraCurrent->getPosition().z);
	skyBox.render();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();


	if (cameraCurrent->getPosition().x < mirrorPosition.x) {
		drawMirrorWorld();
	}

	renderScene();


	//draw physical mirror
	glPushMatrix();
	glTranslatef(mirrorPosition.x, mirrorPosition.y, mirrorPosition.z);
	glScalef(10, 7, 14);
	glRotatef(-90, 0, 1, 0);
	mirror.render();
	glPopMatrix();

	//renderShadows();
	//
	//
	//
	//
	// MAKE A COOL MISSILE LAUNCHER OR SMTHN
	//
	//
	//
	//
	//
	//
	//
	//
	 
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
