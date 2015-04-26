#include "StudentPreProcessing.h"


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
	IntensityImage* newObject = new IntensityImageStudent(image.getWidth,image.getHeight);


	for (int x = 0; x < image.getWidth; x++){
		for (int y = 0; y < image.getHeight; y++){
			double = image.getPixel(x, y); // wat voor waarde moet dit zijn?
			if (){ //check hier of het rood is
			}
			else if(){ //check hier of het groen is

			}
			else if (){ //check hier of het blauw is
			}
			else{ // hier is het dus een andere waarde
			}



			}
		}

	}


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