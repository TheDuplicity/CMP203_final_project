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

	// make table spin
	tableSpin = false;
	tableSpinSpeed = 45;

	glutSetCursor(GLUT_CURSOR_NONE);

	//sort out other rotations for both the sword and the teapot
	tempRotate = 0;
	swordRotation = 0;
	swordOrbit = 0;

	// draw the mirror at these coords
	mirrorPosition.x = 5.0;
	mirrorPosition.y = 2.0;
	//use to make sure shadows dont register the spheres around the lights
	shadowCheck = 0;

	//used to go into different input modes for light controls and camera controls
	userInputSelect = 1;

	//used to generate the scrolling shaoe between the 3 options provided in the shape class
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
	shapeChanger.loadColour(0.8, 0.5, 0.8, 1.f);
	shapeChanger.loadShape(SH_SQUARE);
	shapeChanger.setIsTextured(false);
	wall.loadTexture(&wallTexture);
	wall.loadShape(SH_PLANE);
	wall.setIsTextured(true);

	//lights
	mainLight.setLightPosition(new GLfloat[4]{ -2,9,-5,1 });
	mainLight.setLightAmbient(new GLfloat[4]{ 1.,1.,1.,1 });
	mainLight.setLightDiffuse(new GLfloat[4]{ 1.,1.,1.,1 });
	mainLight.setConstantAttenuation(0.1);
	mainLight.setLinearAttenuation(0.05);
	mainLight.setQuadraticAttenuation(0.02);
	mainLight.setUpLightBulb(&mirrorTexture, SH_CUBE, new GLfloat[4]{1,1,1,1}, false, true);
	mainLight.setThisLight(GL_LIGHT0);


	mainLight.setLightAmbient(new GLfloat[4]{ 0,0,0,1 });
	flashLight.setLightPosition(new GLfloat[4]{ -0.1,0,-13.6,1.f });
	flashLight.setLightDiffuse(new GLfloat[4]{ 10,10,10,1.f });
	flashLight.setLightSpot(new GLfloat[3]{ 0.f,0.f,-1.f});
	flashLight.setConstantAttenuation(0.1);
	flashLight.setLinearAttenuation(0.05);
	flashLight.setQuadraticAttenuation(0.01);
	flashLight.setUpLightBulb(&mirrorTexture, SH_CUBE, new GLfloat[4]{ 1,1,1,1 }, false, true);
	flashLight.setThisLight(GL_LIGHT1);
	flashLight.setIsSpotLight(true);
	
	flashingLight.setLightPosition(new GLfloat[4]{ -40,5,-10,1 });
	flashingLight.setLightAmbient(new GLfloat[4]{ 1.,1.,1.,1 });
	flashingLight.setLightDiffuse(new GLfloat[4]{ 1.,1.,1.,1 });
	flashingLight.setConstantAttenuation(0.0);
	flashingLight.setLinearAttenuation(0.0);
	flashingLight.setQuadraticAttenuation(0.0);
	flashingLight.setUpLightBulb(&mirrorTexture, SH_CUBE, new GLfloat[4]{ 1,1,1,1 }, false, true);
	flashingLight.setThisLight(GL_LIGHT2);

	
	colouredLight.setLightPosition(new GLfloat[4]{ 40, 10,-12, 1 });
	colouredLight.setLightAmbient(new GLfloat[4]{ 0,0.,0.,1 });
	colouredLight.setLightDiffuse(new GLfloat[4]{ 1.,1.,1.,1 });
	colouredLight.setConstantAttenuation(0.1);
	colouredLight.setLinearAttenuation(0.05);
	colouredLight.setQuadraticAttenuation(0.02);
	colouredLight.setUpLightBulb(&mirrorTexture, SH_CUBE, new GLfloat[4]{ 1,1,1,1 }, false, true);
	colouredLight.setThisLight(GL_LIGHT3);

	
	//set the current light
	currentLight = &mainLight;

	//set how far the coloured light will travel in the x and y direction
	colouredLightLimitsMax = colouredLight.getLightPosition()[0] + 10;
	colouredLightLimitsMin = colouredLight.getLightPosition()[0] - 10;
	//set how fast the light moves
	colouredLightVelocity = 5;

	
}

void Scene::renderShadows() {
	//set shadowcheck so when drawing the shadows, the shperes around the lights and the floor and ceiling arent used
	shadowCheck = 1;
	// setup the shadows
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	// set the colour of the shadow to be based on the colour of the light
	glColor4f(mainLight.getLightDiffuse()[0] / 5.0, mainLight.getLightDiffuse()[1] / 5.0, mainLight.getLightDiffuse()[2] / 5.0, .4f);
	//move the shadows up slightly so they dont z fight with the floor. not using depth test so they arent drawn in front of the wrong things
	glTranslatef(0,0.1,0);
	// generate the shadow, only being done for the 1 light but doing the others would be copying this code and using the position of each light
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

	//setup the lighting etc to be used in the normal render
	glColor4f(1.0f, 1.0f, 1.0f,1.f);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);

	glPopMatrix();
	// tell the program that it can draw planes and lights again
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

	//flashlight light source plus lightbulb
	glPushMatrix();
	flashLight.render();
	glPopMatrix();
	// these objects will not be drawn if shadows are being created
	if (shadowCheck == 0) {
		//rendering the lights
		mainLight.render();


		colouredLight.render();

		flashingLight.render();

		//rendering the floor and ceiling
		glPushMatrix();
		glTranslatef(0, -3, 0);
		glScalef(3, 3, 3);
		floor.render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 14, 0);
		glScalef(5, 5, 5);
		ceiling.render();
		glPopMatrix();
	}

	//render the flashlight around the flashlight light source and then rotate it to face the direction the camera is facing
	glPushMatrix();
	glTranslatef(flashLight.getLightPosition()[0], flashLight.getLightPosition()[1], flashLight.getLightPosition()[2]);
	glRotatef(-cameraPlayer1P.getYaw(), 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	flashLightModel.render();
	glPopMatrix();


	//render the wall
	glPushMatrix();
	glTranslatef(0,0,-17);
	glRotatef(90,1,0,0);
	glScalef(0.6,0.6,0.6);
	glScalef(2, 2, 2);
	wall.render();
	glPopMatrix();


	// cube is rendered seperately from the rest of the scene
	glPushMatrix();
	glTranslatef(0, 2, 0);
	square.render();
	glPopMatrix();


	// table and the objects on it are rendered using hierarchical modelling and a miniature version is rendered on the tabletop
	glPushMatrix();
	glTranslatef(-10, -3, 0);
	if (tableSpin == true) {
		glRotatef(tableSpinSpeed, 0, 1, 0);
	}
	glPushMatrix();
	renderTableObjects();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 5, 0);
	glScalef(0.1,0.1,0.1);
	renderTableObjects();
	glPopMatrix();
	glPopMatrix();
	

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
	//using this to ensure dt being too large doesnt result in large distance moving
	if (dt > 1) {
		dt = 0;
	}
	//rotation pitch(x) yaw(y) roll(z) based on mouse position
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
	//movements in camera direction but wasd is restriced to moving along z and x axis
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
	//use spacebar and e to move up and down but you only move up and down along the y axis and you do not move in the other axis
	//up down
	if (input->isKeyDown(32)) {
		cameraCurrent->setPosition(cameraCurrent->getPosition() + Vector3(0/*cameraSpeed * dt * cameraCurrent->getUp().x*/, cameraSpeed * dt * cameraCurrent->getUp().y, 0/* cameraSpeed * dt * cameraCurrent->getUp().z*/));
		cameraCurrent->update();
	}
	if (input->isKeyDown('e')) {
		cameraCurrent->setPosition(cameraCurrent->getPosition() - Vector3(0/*cameraSpeed * dt * cameraCurrent->getUp().x*/, cameraSpeed * dt * cameraCurrent->getUp().y, 0/*cameraSpeed * dt * cameraCurrent->getUp().z*/));
		cameraCurrent->update();
	}

	// move the flashlight to be where the player camera is
	flashLight.setLightPosition(new GLfloat[4]{ cameraPlayer1P.getPosition().x /*- ((float)1 * cameraPlayer1P.getForward().x)*/,
		cameraPlayer1P.getPosition().y - 1/*+ ((float)3 * cameraPlayer1P.getForward().y)*/,
		cameraPlayer1P.getPosition().z , 1.f });
	// set the direction of the flashlight to be the direction the camera faces
	flashLight.setLightSpot(new GLfloat[3]{ cameraPlayer1P.getForward().x,cameraPlayer1P.getForward().y,cameraPlayer1P.getForward().z });

}
void Scene::userInputLight(float dt) {
	if (dt > 1) {
		dt = 0;
	}
	// move the light around
	if (input->isKeyDown('w')) {
		currentLight->getLightPosition()[1] += 6 * dt;
	}
	if (input->isKeyDown('s')) {
		currentLight->getLightPosition()[1] -= 6 * dt;
	}
	if (input->isKeyDown('d')) {
		currentLight->getLightPosition()[0] += 6 * dt;
	}
	if (input->isKeyDown('a')) {
		currentLight->getLightPosition()[0] -= 6 * dt;
	}
	if (input->isKeyDown('q')) {
		currentLight->getLightPosition()[2] += 6 * dt;
	}
	if (input->isKeyDown('e')) {
		currentLight->getLightPosition()[2] -= 6 * dt;
	}

}

void Scene::handleInput(float dt)
{
	if (dt > 1) {
		dt = 0;
	}
	// if the user presses '1' they go into camera control mode where they can move the camera and if they press '2' they can move the lights of their choice
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
	// combining the 'c' press and the number keys let you select a camera
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
	// combing the 'l' key and pressing the number keys allows you to manipulated the different lights when you are in the light manipulation mode
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
		else if (input->isKeyDown('4')) {
			currentLight = &flashLight;
		}

	}
	// if you arent controlling the light selection or camera selection, then the numbers 1 and 2 will let you go into camera control or light control mode
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
	// using the minus key allows for wireframe mode and the equals keyy brings it back to fill mode
	if (input->isKeyDown('-')) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);

	}
	else if (input->isKeyDown('=')) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	// pressing 't' acttivaties the table and its contents to rotate and pressing 'y' stops and resets it back to its original position
	if (input->isKeyDown('t')) {
		tableSpin = true;
	}
	if(input->isKeyDown('y')){
		tableSpin = false;
	}
	//place the cursor back into the middle for camera calculations
	glutWarpPointer(width / 2.0, height / 2.0);
}

void Scene::update(float dt)
{
	if (dt > 1) {
		dt = 0;
	}
	// setup timers
	swapShapeTimer += dt;
	colourChangeTimer += dt;
	// update scene related variables.

	//setup rotations
	tempRotate += 90 * dt;
	swordRotation += 270 * dt;
	swordOrbit += -90 * dt;
	if (swordRotation >= 360) {
		swordRotation = 0;
	}
	if (swordOrbit >= 360) {
		swordOrbit = 0;
	}
	//rotate the sword camera which just goes in circles near the scene.
	swordCamera.setYaw(swordOrbit);
	if (cameraCurrent == &swordCamera) {
		
		swordCamera.update();
		swordCamera.setLookAt(Vector3(-10, 4,0));
		//done this so the camera doesnt spawn somewhere really far away and rotates in the middle of nowhere
		if (!swordCameraFixed) {
			swordCameraFixed = true;
		}
	}
	//now we can move the camera in circles
	if (swordCameraFixed) {
		swordCamera.setPosition(swordCamera.getPosition() + Vector3(
			swordCamera.getForward().x * (90.f / 360.f) * (2 * 3.14159 * 10) * dt,
			swordCamera.getForward().y * (90.f / 360.f) * (2 * 3.14159 * 10) * dt,
			swordCamera.getForward().z * (90.f / 360.f) * (2 * 3.14159 * 10) * dt
		));
	}
	// use this every 0.5 seconds to chance the colour of the coloured light
	if (colourChangeTimer > 0.5) {
		srand(time(NULL));
		colourChangeTimer = 0;
		colouredLight.modifyLightDiffuse((float)(rand() % 100) * 0.1, (float)(rand() % 100) * 0.1, (float)(rand() % 100) * 0.1);
	}
	// change the brightness of the light by changing its quadratic attenuation and putting it back to 0.03 once it reaching its limit of 0.1
	flashingLight.setQuadraticAttenuation(flashingLight.getQuadraticAttenuation() + ((float)0.045 * dt));
	if (flashingLight.getQuadraticAttenuation() > 0.1) {
		flashingLight.setQuadraticAttenuation(0.03);
	}
	//makethe table spin at 45 degrees a second
	if (tableSpin) {
		tableSpinSpeed += 45 * dt;
	}
	//change the velocities direction if the light reaches its x min or max limit
	if (colouredLight.getLightPosition()[0] > colouredLightLimitsMax) {
		colouredLightVelocity = -5;
	}
	else if (colouredLight.getLightPosition()[0] < colouredLightLimitsMin) {
		colouredLightVelocity = 5;
	}
	colouredLight.setLightPosition(new GLfloat[4]{ colouredLight.getLightPosition()[0] + (colouredLightVelocity * dt),colouredLight.getLightPosition()[1],colouredLight.getLightPosition()[2],colouredLight.getLightPosition()[3] });
	// Calculate FPS for output
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

	// dont draw the mirror world if you are on the wrong side of the mirror where it shouldnt be visible anymore
	if (cameraCurrent->getPosition().x < mirrorPosition.x) {
		drawMirrorWorld();
	}
	//draw the scene
	renderScene();


	//draw physical mirror
	glPushMatrix();
	glTranslatef(mirrorPosition.x, mirrorPosition.y, mirrorPosition.z);
	glScalef(10, 7, 14);
	glRotatef(-90, 0, 1, 0);
	mirror.render();
	glPopMatrix();
	// draw the shadows
	renderShadows();
	 
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
	timefps = glutGet(GLUT_ELAPSED_TIME);

	if (timefps - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (timefps - timebase));
		timebase = timefps;
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
