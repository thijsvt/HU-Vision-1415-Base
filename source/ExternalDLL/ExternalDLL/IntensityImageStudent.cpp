#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: Create a copy from the other object
	set(other);
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: Initialize pixel storage
	pixelArray = new Intensity*[width];
	for (auto x = 0; x < width; x++){
		pixelArray[x] = new Intensity[height];
	}
}

IntensityImageStudent::~IntensityImageStudent() {
	//int throwError = 0, e = 1 / throwError;
	//TODO: delete allocated objects
	for (auto x = 0; x < getWidth(); x++){
		delete pixelArray[x];
	}
	delete pixelArray;
}

void IntensityImageStudent::set(const int width, const int height) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
	for (auto x = 0; x < getWidth(); x++){
		delete pixelArray[x];
	}
	delete pixelArray;
	IntensityImage::set(width, height);
	pixelArray = new Intensity*[width];
	for (auto x = 0; x < width; x++){
		pixelArray[x] = new Intensity[height];
	}
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	for (auto x = 0; x < getWidth(); x++){
		delete pixelArray[x];
	}
	delete pixelArray;
	IntensityImage::set(other.getWidth(), other.getHeight());
	int width = other.getWidth();
	int height = other.getHeight();
	pixelArray = new Intensity*[width];
	for (auto x = 0; x < width; x++){
		pixelArray[x] = new Intensity[height];
	}
	for (auto x = 0; x < getWidth(); x++){
		for (auto y = 0; y < getHeight(); y++){
			pixelArray[x][y] = other.getPixel(x, y);
		}
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	pixelArray[x][y] = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	//int throwError = 0, e = 1 / throwError;
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
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
	*    
	*/
	int x = i % getWidth(); 
	int y = i / getWidth();
	setPixel(x, y, pixel);
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	//return 0;
	return pixelArray[x][y];
}

Intensity IntensityImageStudent::getPixel(int i) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: see setPixel(int i, RGB pixel)
	//return 0;
	return pixelArray[i % getWidth()][i / getWidth()];
}