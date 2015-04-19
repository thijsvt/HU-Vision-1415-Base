#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	int throwError = 0, e = 1 / throwError;
	//TODO: Create a copy from the other object
	set(other);
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: Initialize pixel storage
	pixelArray = new RGB*[width];

	for (auto x = 0; x < width; x++){
		pixelArray[x] = new RGB[height];
	}
}

RGBImageStudent::~RGBImageStudent() {
	//int throwError = 0, e = 1 / throwError;
	//TODO: delete allocated objects
	for (int x = 0; x < getWidth(); x++){
		delete pixelArray[x];
	}
	delete pixelArray;
}

void RGBImageStudent::set(const int width, const int height) {
	for (int x = 0; x < getWidth(); x++){
		delete pixelArray[x];
	}
	delete pixelArray;

	RGBImage::set(width, height);

	pixelArray = new RGB*[width];

	for (auto x = 0; x < width; x++){
		pixelArray[x] = new RGB[height];
	}

	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
	// this function was explained by daniel van den berg. (thanks alot!) 
	for (int x = 0; x < getWidth(); x++){
		delete pixelArray[x];
	}
	delete pixelArray;
	RGBImageStudent::set(other.getWidth(), other.getHeight()); //create the new one

	int width = other.getWidth(); // get the width
	int height = other.getHeight(); // get the heigth
	pixelArray = new RGB*[width];
	for (int x = 0; x < width; x++){
		pixelArray[x] = new RGB[height];
	}

	for (int x = 0; x < getWidth(); x++){
		for (int y = 0; y < getHeight(); y++){
			pixelArray[x][y] = other.getPixel(x, y);
		}
	}
}

	

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	pixelArray[x][y] = pixel;
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	//int throwError = 0, e = 1 / throwError;
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	*  9 1 2
	*  4 3 5
	*  8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/
	int x = i % getWidth(); //bereken de lengte met het restgetal van i
	int y = i / getWidth(); // bereken de breedte met de deling van y
	setPixel(x, y, pixel); // set de pixel 
}

RGB RGBImageStudent::getPixel(int x, int y) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	//return 0;
	return pixelArray[x][y];
}

RGB RGBImageStudent::getPixel(int i) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: see setPixel(int i, RGB pixel)
	//bereken de lengte met het restgetal van i
	return pixelArray[i %getWidth()][i / getWidth()];
}