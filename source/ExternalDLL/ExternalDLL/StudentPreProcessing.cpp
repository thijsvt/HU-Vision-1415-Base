#include "StudentPreProcessing.h"


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImage* newObject = new IntensityImageStudent(image.getWidth(), image.getHeight());

	for (int x = 0; x < image.getWidth(); x++){
		for (int y = 0; y < image.getHeight(); y++){
			RGB pixel = image.getPixel(x, y); // wat voor waarde moet dit zijn?
			Intensity intensityPixel = Intensity(0.299*pixel.r + 0.587*pixel.g + 0.114*pixel.b);
			newObject->setPixel(x, y, intensityPixel);

			//formule gebaseerd op http://www.songho.ca/dsp/luminance/luminance.html
		}
	}

	return newObject;


	// hoe haal je R G B uit de image

	//IntensityImageStudent::IntensityImageStudent(image);
	//maak een nieuwe opbject aan voor intensity image
	//bereken hier rgb naar intensity
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}