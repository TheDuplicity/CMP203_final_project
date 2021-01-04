#pragma once
#include "Vector3.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
class Camera
{
private:
	//store the info we need to know to correctly position and face the camera

	Vector3 up;
	Vector3 forward;
	Vector3 position;
	Vector3 lookAt;
	Vector3 right;
	float Yaw; // y rot
	float Pitch; // x rot
	float Roll; // z rot
	Vector3 rotSpeed;
	Vector3 rotationLimits;


public:
	Camera();

	//setters and getters for all of the variables stored in the camera so we can update it during the game
	void setPitch(float inpPitch) { Pitch = inpPitch; };
	float getPitch() { return Pitch; };
	void setRoll(float inpRoll) { Roll = inpRoll; };
	float getRoll() { return Roll; };
	void setYaw(float inpYaw) { Yaw = inpYaw; };
	float getYaw() { return Yaw; };

	void setRotSpeed(Vector3 inpRotSpeed) { rotSpeed = inpRotSpeed; };
	Vector3 getRotSpeed() { return rotSpeed; };

	void setUp(Vector3 upwards) { up = upwards; };
	Vector3 getUp() { return up; };
	void setForward(Vector3 forwards) { forward = forwards; };
	Vector3 getForward() { return forward; };
	void setPosition(Vector3 cameraPosition) { position = cameraPosition; };
	Vector3 getPosition() { return position; };
	void setLookAt(Vector3 lookPos) { lookAt = lookPos; };
	Vector3 getLookAt() { return lookAt; };
	void setRight(Vector3 cameraRight) { right = cameraRight; };
	Vector3 getRight() { return right; };


	void update();
};


