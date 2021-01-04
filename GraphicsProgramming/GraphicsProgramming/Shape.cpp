#include "Shape.h"
Shape::Shape() {
	//set default variables for the shape so it can run straight off the bat
	loadShape(SH_CUBE);
	renderType = SH_INDEX;
	texture = NULL;
	for (int i = 0; i < 4; i++)
	{
		materialColour[i] = 1.f;
	}
	isTransparent = false;
	isTextured = true;

}
Shape::Shape(GLuint* inpTexture) {
	//set default variables for the shape so it can run straight off the bat
	loadShape(SH_CUBE);
	renderType = SH_INDEX;
	texture = NULL;
	for (int i = 0; i < 4; i++)
	{
		materialColour[i] = 1.f;
	}
	isTransparent = false;
	isTextured = true;
	texture = inpTexture;

}
void Shape::loadShape(int selectedShape) {
	// clear all of the current info about the shape so the new shape can be placed into the arrays to be created properly
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indeces.clear();
	//based on which shape is chosen, a different shape is created
	switch (selectedShape)
	{
	case SH_SQUARE:
		setSquare();
		break;
	case SH_CUBE:
		setCube();
		break;
	case SH_PYRAMID:
		setPyramid();
		break;
	case SH_SKYBOX:
		setSkyBox();
		break;
	case SH_PLANE:
		setPlane();
		break;
	default:
		break;
	}
}
//this will allow the user tochange the scolour of the shape
void Shape::loadColour(float r, float g, float b, float a) {
	materialColour[0] = r;
	materialColour[1] = g;
	materialColour[2] = b;
	materialColour[3] = a;
	
}
//create a cube but remap the texture coords to work for the skybox texture i have
bool Shape::setSkyBox() {
	setCube();
	textureCoords.clear();
	//front  	// TL BL BR, TL BR TR
	textureCoords.push_back(0.5);
	textureCoords.push_back(1 / 3.0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(1 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(1 / 3.0);
	//back
	textureCoords.push_back(0.75);
	textureCoords.push_back(1 / 3.0);

	textureCoords.push_back(0.75);
	textureCoords.push_back(2/3.0);

	textureCoords.push_back(1);
	textureCoords.push_back(2/3.0);

	textureCoords.push_back(0.75);
	textureCoords.push_back(1/3.0);

	textureCoords.push_back(1);
	textureCoords.push_back(2/3.0);

	textureCoords.push_back(1);
	textureCoords.push_back(1/3.0);
	//left  	//BL BR TL, BR TL TR 
	textureCoords.push_back(0.75);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.75);
	textureCoords.push_back(1 / 3.0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.75);
	textureCoords.push_back(1 / 3.0);


	textureCoords.push_back(0.5);
	textureCoords.push_back(1 / 3.0);

	//right
	textureCoords.push_back(0);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.);
	textureCoords.push_back(1 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0);
	textureCoords.push_back(1 / 3.0);


	textureCoords.push_back(0.25);
	textureCoords.push_back(1 / 3.0);

	//top  	// TL BL BR, TL BR TR
	textureCoords.push_back(0.5);
	textureCoords.push_back(0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(1 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(1 / 3.0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(1 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(0);

	//bottom
	textureCoords.push_back(0.25);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(3 / 3.0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(3 / 3.0);

	textureCoords.push_back(0.25);
	textureCoords.push_back(2 / 3.0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(3 / 3.0);

	textureCoords.push_back(0.5);
	textureCoords.push_back(2 / 3.0);

	return true;

}
//create all the data for each of the shapes
bool Shape::setSquare() {
	// render type tells us whether or not to use indices or just vertices to create the shape
	renderType = SH_INDEX;
	//store vertices so we have all the triangles to create the shape
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(0);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(0);

	//for shapes that need indeces like the square, set its indices
	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(2);
	indeces.push_back(1);
	indeces.push_back(2);
	indeces.push_back(3);

	//map the relevant texture coords for each vertex or index
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	textureCoords.push_back(0);

	//set the normals so lighting works properly

	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	return true;
}
bool Shape::setCube() {
	renderType = SH_VERTEX;
	//front

	// TL BL BR, TL BR TR

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);


	//back
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);

	//left
	
	//BL BR TL, BR TL TR 

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);
	
	//right

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);

	//top

	// TL BL BR, TL BR TR

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	//bottom

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);


	/* cube via indeces
	// front incices
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);

	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);


	//back indeces
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);


	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);


	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);


	vertices.push_back(0.5);
	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);

	//in front
	// 2 3
	// 0 1
	// behind
	// 6 7
	// 4 5

	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(2);
	indeces.push_back(1);  //front
	indeces.push_back(2);
	indeces.push_back(3);

	indeces.push_back(5);
	indeces.push_back(4);
	indeces.push_back(7);
	indeces.push_back(4); // back
	indeces.push_back(7);
	indeces.push_back(6);

	indeces.push_back(4);
	indeces.push_back(0);
	indeces.push_back(6);
	indeces.push_back(0); // left
	indeces.push_back(6);
	indeces.push_back(2);

	indeces.push_back(1);
	indeces.push_back(5);
	indeces.push_back(3);
	indeces.push_back(5); //right
	indeces.push_back(3);
	indeces.push_back(7);
	
	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(4);
	indeces.push_back(1); // below
	indeces.push_back(4);
	indeces.push_back(5);

	indeces.push_back(2);
	indeces.push_back(3);
	indeces.push_back(6);
	indeces.push_back(3); // above
	indeces.push_back(6);
	indeces.push_back(7);
	*/
	
	return true;
}
bool Shape::setSphere() {
	renderType = SH_VERTEX;
	return true;
}
bool Shape::setPlane() {
	renderType = SH_VERTEX;
	Vector3 currentPosition = (0,0,0);
	//create a plane of squares where the z and x values in the loops tell you how many squares are made for each axis (x100,z100)
	for (int z = -50; z < 50; z++) {
		for (int x = -50; x < 50; x++) {

			vertices.push_back(currentPosition.x + -0.5);
			vertices.push_back(currentPosition.y + 0);
			vertices.push_back(currentPosition.z + -0.5);
			textureCoords.push_back(0);
			textureCoords.push_back(0);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			vertices.push_back(currentPosition.x + -0.5);
			vertices.push_back(currentPosition.y + 0);
			vertices.push_back(currentPosition.z + 0.5);
			textureCoords.push_back(0);
			textureCoords.push_back(1);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			vertices.push_back(currentPosition.x + 0.5);
			vertices.push_back(currentPosition.y + 0);
			vertices.push_back(currentPosition.z + 0.5);
			textureCoords.push_back(1);
			textureCoords.push_back(1);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			vertices.push_back(currentPosition.x + -0.5);
			vertices.push_back(currentPosition.y + 0);
			vertices.push_back(currentPosition.z + -0.5);
			textureCoords.push_back(0);
			textureCoords.push_back(0);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			vertices.push_back(currentPosition.x + 0.5);
			vertices.push_back(currentPosition.y + 0);
			vertices.push_back(currentPosition.z + 0.5);
			textureCoords.push_back(1);
			textureCoords.push_back(1);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			vertices.push_back(currentPosition.x + 0.5);
			vertices.push_back(currentPosition.y + 0);
			vertices.push_back(currentPosition.z + -0.5);
			textureCoords.push_back(1);
			textureCoords.push_back(0);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			currentPosition.x = x;
		}
		currentPosition.z = z;
	}
	return true;
}
bool Shape::setPyramid() {
	renderType = SH_INDEX;
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);

	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);

	vertices.push_back(0.5);
	vertices.push_back(-0.5);
	vertices.push_back(-0.5);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);

	vertices.push_back(0);
	vertices.push_back(0.5);
	vertices.push_back(0);
	textureCoords.push_back(0.5);
	textureCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);

	// 2   3
	//   4
	// 0   1 
	
	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(2);

	indeces.push_back(2);
	indeces.push_back(1);
	indeces.push_back(3);

	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(4);

	indeces.push_back(1);
	indeces.push_back(4);
	indeces.push_back(3);

	indeces.push_back(3);
	indeces.push_back(2);
	indeces.push_back(4);

	indeces.push_back(2);
	indeces.push_back(0);
	indeces.push_back(4);
	

	return true;
}

void Shape::render() {
	// if its transparent, enable blend
	if(isTransparent){
		glEnable(GL_BLEND);
	}
	// if its textured, enable textures and load the texture for the shape
	if (isTextured) {
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else {
		// disable textures if you dont have one
		glDisable(GL_TEXTURE_2D);
	}

		// set the material colour so the shape has the right colour
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColour);

		//then set up the arrays with the shape data and format them to accept it in its current format
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
		glNormalPointer(GL_FLOAT, 0, &normals[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &textureCoords[0]);
		//based on vertex or index shape, draw the shape using the data stored
		if (renderType == SH_INDEX) {
			glDrawElements(GL_TRIANGLES, indeces.size(), GL_UNSIGNED_INT, &indeces[0]);
		}
		else if (renderType == SH_VERTEX) {
			glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);
		}

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	// gidable blend or enable textures if you have them enabled/disabled to reset
	if (isTransparent) {
		glDisable(GL_BLEND);
	}
	if (!isTextured) {
		glEnable(GL_TEXTURE_2D);
	}

}