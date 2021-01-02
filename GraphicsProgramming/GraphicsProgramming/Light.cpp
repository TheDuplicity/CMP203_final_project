#include "Light.h"
Light::Light() {
	thisLight = GL_LIGHT0;
	for (int i = 0; i < 4; i++) {
		lightAmbient[i] = 1.f;
		lightDiffuse[i] = 1.f;
		lightPosition[i] = 0.f;
		lightSpot[i] = 0.f;
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
	glPushMatrix();
	glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
	glScalef(0.1,0.1,0.1);
	lightBulb.render();
	glPopMatrix();
}

void Light::applyLightParameters(bool spotLight) {

	glLightf(thisLight, GL_CONSTANT_ATTENUATION, constantAttenuation);
	glLightf(thisLight, GL_LINEAR_ATTENUATION, linearAttenuation);
	glLightf(thisLight, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);

	glLightfv(thisLight, GL_AMBIENT, lightAmbient);
	glLightfv(thisLight, GL_DIFFUSE, lightDiffuse);
	glLightfv(thisLight, GL_POSITION, lightPosition);
	if (spotLight) {
		glLightf(thisLight, GL_SPOT_CUTOFF, 25.0f);
		glLightfv(thisLight, GL_SPOT_DIRECTION, lightSpot);
		glLightf(thisLight, GL_SPOT_EXPONENT, 50.0);
	}

	glEnable(thisLight);


}
