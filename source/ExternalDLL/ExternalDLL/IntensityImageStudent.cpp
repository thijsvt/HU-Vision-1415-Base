#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	//int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
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
		delete [] pixelArray[x];
	}
	delete [] pixelArray;
}

void IntensityImageStudent::set(const int width, const int height) {
	if (pixelArray == nullptr){
		pixelArray = new Intensity*[width];
		for (auto x = 0; x < width; x++){
			pixelArray[x] = new Intensity[height];
		}
	}
	else{
		pixelArrayCopy = new Intensity*[width];
		for (auto x = 0; x < width; x++){
			pixelArrayCopy[x] = new Intensity[height];
		}
		for (int p = 0; p < getWidth(); p++){
			for (int y = 0; y < getHeight(); y++){
				if (p > width || y > height){
					//afvangen of hij niet groter is
				}
				else{
					pixelArrayCopy[p][y] = pixelArray[p][y];
				}
			}
		}
		for (int x = 0; x < getWidth(); x++){
			delete[] pixelArray[x];
		}
		delete[] pixelArray;
		pixelArray = pixelArrayCopy; //pointer van pixelarray naar pixelarracopy laten wijzen
	}
	IntensityImage::set(width, height); // deze moet altijd
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
	// this function was explained by daniel van den berg. (thanks alot!) 
	for (int x = 0; x < getWidth(); x++){
		delete[] pixelArray[x];
	}
	delete[] pixelArray;
	IntensityImageStudent::set(other.getWidth(), other.getHeight()); //create the new one
	//weggooien en nieuw geheugen aanmaken wordt al gedaan hierboven.
	for (int x = 0; x < getWidth(); x++){
		for (int y = 0; y < getHeight(); y++){
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