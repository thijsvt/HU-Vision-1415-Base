#include "StudentPreProcessing.h"


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImage* newObject = new IntensityImageStudent(image.getWidth(), image.getHeight());

	for (int x = 0; x < image.getWidth(); x++){
		for (int y = 0; y < image.getHeight(); y++){
			RGB pixel = image.getPixel(x, y); // wat voor waarde moet dit zijn?
			Intensity intensityPixel = Intensity(0.2989*pixel.r + 0.5870*pixel.g + 0.1140*pixel.b);
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
	// eerst noise reduction
	// dan edge enhanchement
	// en dan edge localisation
	// maak gebruik van laplacian (zie neighbourhoud operations 170) (werkt samen met guaccian)
	// Pas daarna een LOG filter toe of als je wilt heb je DOG
	// Handige links : http://homepages.inf.ed.ac.uk/rbf/HIPR2/log.htm 
	// handige links http://softwarebydefault.com/tag/laplacian-of-gaussian/



	
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}