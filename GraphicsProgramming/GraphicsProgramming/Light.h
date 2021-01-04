#pragma once
#include "Shape.h"
class Light
{
public:
	Light();

	void render();

	void setThisLight(float newLight) { thisLight = newLight; };

	void modifyLightDiffuse(float r, float g, float b) {
		lightDiffuse[0] = r;
		lightDiffuse[1] = g;
		lightDiffuse[2] = b;
		glLightfv(thisLight, GL_DIFFUSE, lightDiffuse);
	}

	void setLightDiffuse(GLfloat inpLightDiffuse[]) { 
		for (int i = 0; i < 4; i++)
		{ lightDiffuse[i] = inpLightDiffuse[i]; }
	};

	void setLightAmbient(GLfloat inpLightAmbient[]) {
		for (int i = 0; i < 4; i++)
		{
			lightAmbient[i] = inpLightAmbient[i];
		}
	};

	void setLightPosition(GLfloat inpLightPosition[]) {
		for (int i = 0; i < 4; i++)
		{
			lightPosition[i] = inpLightPosition[i];
		}
	};

	void setLightSpot(GLfloat inpLightSpot[]) {
		for (int i = 0; i < 3; i++)
		{
			lightSpot[i] = inpLightSpot[i];
		}
	};

	GLfloat getQuadraticAttenuation() { return quadraticAttenuation; };
	GLfloat getLinearAttenuation() { return linearAttenuation; };
	GLfloat getConstantAttenuation() { return constantAttenuation; };

	void setConstantAttenuation(GLfloat inputConstantAttenuation) { constantAttenuation = inputConstantAttenuation; };
	void setLinearAttenuation(GLfloat inputLinearAttenuation) { linearAttenuation = inputLinearAttenuation; };
	void setQuadraticAttenuation(GLfloat inputQuadraticAttenuation) { quadraticAttenuation = inputQuadraticAttenuation; };

	void setIsSpotLight(GLboolean spotLight) { isSpotLight = spotLight; };

	void applyLightParameters();

	void setUpLightBulb(GLuint *texture, int shape, GLfloat colour[], bool isTransparent, bool isTextured);

	GLfloat* getLightDiffuse() {return lightDiffuse; };
	GLfloat* getLightPosition() { return lightPosition; };
	GLfloat* getLightAmbient() { return lightAmbient; };
	GLfloat* getLightSpot() { return lightSpot; };
private:
	GLfloat lightDiffuse[4];
	GLfloat lightAmbient[4];
	GLfloat lightPosition[4];
	GLfloat lightSpot[3];
	GLfloat constantAttenuation;
	GLfloat linearAttenuation;
	GLfloat quadraticAttenuation;
	GLuint thisLight;
	GLboolean isSpotLight;
	Shape lightBulb;
};

