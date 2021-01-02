#include "Camera.h"
Camera::Camera() {
	position.x = 0, position.y = 0, position.z = 6;
	forward.x = 0, forward.y = 0, forward.z = -1;
	Yaw = 0, Pitch = 0, Roll = 0;
	rotSpeed.x = 5, rotSpeed.y = 3, rotSpeed.z = 10;
	rotationLimits.x = 90, rotationLimits.y = 361, rotationLimits.z = 45;


}


void Camera::update() {
	if (Pitch > rotationLimits.x) {
		Pitch = rotationLimits.x;
	}
	else if (Pitch < - rotationLimits.x) {
		Pitch = -90;
	}
	float cosR, cosP, cosY;
	//temp values for sin/cos from 
	float sinR, sinP, sinY;
	// Roll, Pitch and Yallare variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(Yaw * 3.1415 / 180);
	cosP = cosf(Pitch * 3.1415 / 180);
	cosR = cosf(Roll * 3.1415 / 180);
	sinY = sinf(Yaw * 3.1415 / 180);
	sinP = sinf(Pitch * 3.1415 / 180);
	sinR = sinf(Roll * 3.1415 / 180);

	//This using the parametric equation of a sphere
	// Calculate the three vectors to put into  gluLookat
	// Look direction,  position and the up vector
	// This function could also calculate the right vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.
	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	// If you don’t need to calculate this,  don’t do it.

	lookAt = Vector3(position.x + forward.x, position.y + forward.y, position.z + forward.z);

	right = forward.cross(up);
}