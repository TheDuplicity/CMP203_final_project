#include "Shape.h"
Shape::Shape() {
	//drawPyramid();
	drawCube();
	//drawSquare();

}
Shape::Shape(GLuint* inpTexture) {
	//drawPyramid();
	drawCube();
	//drawSquare();
	texture = inpTexture;

}
bool Shape::drawSquare() {
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

	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(2);
	indeces.push_back(1);
	indeces.push_back(2);
	indeces.push_back(3);

	textureCoords.push_back(0);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	textureCoords.push_back(1);
	textureCoords.push_back(0);
	textureCoords.push_back(0);
	textureCoords.push_back(1);
	textureCoords.push_back(0);

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
bool Shape::drawCube() {
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
	
	return true;
}
bool Shape::drawSphere() {

	return true;
}
bool Shape::drawPyramid() {
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



	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textureCoords[0]);

	glDrawElements(GL_TRIANGLES, indeces.size(), GL_UNSIGNED_INT, &indeces[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}