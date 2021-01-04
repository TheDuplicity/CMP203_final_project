#include "Light.h"
Light::Light() {
	// initialise variables so any new light works immediately (apart from which light it is, that needs to be changed to LIGHT_(0 + how many lights have been made))
	constantAttenuation = 0.1;
	linearAttenuation = 0.05;
	quadraticAttenuation = 0.03;
	isSpotLight = false;
	thisLight = GL_LIGHT0;
	for (int i = 0; i < 4; i++) {
		lightAmbient[i] = 0.1f;
		lightDiffuse[i] = 0.1f;
		lightPosition[i] = 0.f;
		// i need a position for the lights instead of them being directional lights so i put 1's at the end
		if (i == 3) {
			lightPosition[i] = 1.f;
			lightAmbient[i] = 1.f;
			lightDiffuse[i] = 1.f;
		}
		// the spotlight should be filled with 3 0's with no fourth element
		if (i < 3) {
			lightSpot[i] = 0.f;
		}
	}

}
void Light::setUpLightBulb(GLuint* texture, int shape, GLfloat colour[], bool isTransparent, bool isTextured) {
	lightBulb.loadTexture(texture);
	lightBulb.loadColour(colour[0], colour[1], colour[2], colour[3]);
	lightBulb.loadShape(shape);
	lightBulb.setIsTextured(isTextured);
	lightBulb.setIsTransparent(isTransparent);
}

void Light::render() {
	//update the lights every frame in case they move or values within  them are changed
	applyLightParameters();

	glPushMatrix();
	//create a lightbulb where the light is so it can be visualised
	glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);

	// i have a lightbulb but using a sphere looks better than any shapes or models i have
	//glScalef(0.1,0.1,0.1);
	//lightBulb.render();


	gluSphere(gluNewQuadric(), 0.05, 15, 15);
	glPopMatrix();
}

void Light::applyLightParameters() {
	//this will update all the light information to set its birghtness, colour, direction etc
	glLightf(thisLight, GL_CONSTANT_ATTENUATION, constantAttenuation);
	glLightf(thisLight, GL_LINEAR_ATTENUATION, linearAttenuation);
	glLightf(thisLight, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);

	glLightfv(thisLight, GL_AMBIENT, lightAmbient);
	glLightfv(thisLight, GL_DIFFUSE, lightDiffuse);
	glLightfv(thisLight, GL_POSITION, lightPosition);
	// only apply spotlight parameters if the user has specified it is a spotlight
	if (isSpotLight) {
		glLightf(thisLight, GL_SPOT_CUTOFF, 15.0f);
		glLightfv(thisLight, GL_SPOT_DIRECTION, lightSpot);
		glLightf(thisLight, GL_SPOT_EXPONENT, 150.0);
	}
	// thisLight allows the user to create a new light every time they want one and all they have to do is input GL_LIGHT(x) to get the new light to work properly
	glEnable(thisLight);


}
