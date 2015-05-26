#include "StudentPreProcessing.h"


const int StudentPreProcessing::kernel5x5[5][5] =
{ { 2, 4, 5, 4, 2 }, // = 17
{ 4, 9, 12, 9, 4 }, 
{ 5, 12, 15, 12, 5 },
{ 4, 9, 12, 9, 4 },
{ 2, 4, 5, 4, 2 }, }; // =17
// = 159

const int StudentPreProcessing::LapKernel5x5[5][5] =
{ { -1, -1, -1, -1, -1, },
{ -1, -1, -1, -1, -1, },
{ -1, -1, 24, -1, -1, },
{ -1, -1, -1, -1, -1, },
{ -1, -1, -1, -1, -1 }}; //laplacian kernel is het gewicht altijd 0

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
	// maak gebruik van laplacian (zie neighbourhood operations 170) (werkt samen met gaussian)
	// Pas daarna een LOG filter toe of als je wilt heb je DOG
	// Handige links : http://homepages.inf.ed.ac.uk/rbf/HIPR2/log.htm 
	// handige links: http://softwarebydefault.com/tag/laplacian-of-gaussian/
	// handige links: http://www.programming-techniques.com/2013/02/gaussian-filter-generation-using-cc.html

	// stap 2. Ga door met aan de threshold kloten totdat de image er beter uitziet. 
	//(mogelijk heid om de image nog beter te krijgen is er door de waardes aan te gaan passen zie kjeld voor meer info)

	auto valueImage = new IntensityImageStudent(image.getWidth()-4, image.getHeight()-4);
	auto valueImageLap = new IntensityImageStudent(valueImage->getWidth() - 4, valueImage->getHeight() - 4);
	// -4 bij de value image om te zorgen dat de kernel niet buiten de rand van de image valt.
	// x,y = 2 om hier aan te kunnen voldoen. zie alfbeelding Jospixeluitleg.png
	for (int x = 2; x < image.getWidth()-2; x++){
		for (int y = 2; y < image.getHeight()-2; y++){
			int newIntensity = 0;

			for (int g = -2; g < 3; g++){
				for (int q = -2; q < 3; q++){
					//+2 om de omliggende pixels mee te pakken.
					newIntensity += image.getPixel(x + g, y + q) * (kernel5x5[g + 2][q + 2]);
				}
			}
			valueImage->setPixel(x-2, y-2, static_cast<unsigned char>(newIntensity/159.0));
		}
	}

	for (int x = 2; x < valueImage->getWidth() - 2; x++){
		for (int y = 2; y < valueImage->getHeight() - 2; y++){
			int newIntensity = 0;

			for (int g = -2; g < 3; g++){
				for (int q = -2; q < 3; q++){
					//+2 om de omliggende pixels mee te pakken.
					newIntensity += valueImage->getPixel(x + g, y + q) * (LapKernel5x5[g + 2][q + 2]);
				}
			}
			if (newIntensity > 255){
				newIntensity = 255;
			}
			else if (newIntensity < 0){
				newIntensity = 0;
			}
			valueImageLap->setPixel(x - 2, y - 2, static_cast<unsigned char>(newIntensity));
		}
	}
	return valueImageLap;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	//threshold pakt de pixel en gooi je in de nieuwe image. 
	auto valueImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	for (int i = 0; i < image.getWidth(); i++){
		for (int j = 0; j < image.getHeight(); j++){
			valueImage->setPixel(i, j, image.getPixel(i, j));
		}
	}

	//The simplest thresholding methods replace each pixel in an image with a black pixel if the image intensity I_{i,j} is less than some fixed constant T (that is, I_{i,j}<T), or a white pixel if the image intensity is greater than that constant. In the example image on the right, this results in the dark tree becoming completely black, and the white snow becoming complete white.
	// http://en.wikipedia.org/wiki/Otsu%27s_method
	// http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
	int histData[256]; // zijn de RGB waardes oko wel intesity 
	int threshold;
	int ptr = 0;
	int maxLevelValue = 0;
	int aantalpixels = image.getHeight() * image.getWidth();
	while (ptr < aantalpixels){
		int h = 0XFF & image.getPixel(ptr);
		histData[h]++;
		if (histData[h] > maxLevelValue) maxLevelValue = histData[h];
		ptr++;
	}

	
	float sum = 0;
	for (int t = 0; t < 256; t++){
		sum += t*histData[t];

	}

	float sumB = 0;
	int wB = 0;
	int wF = 0;

	float varMax = 0;
	threshold = 0;

	for (int t = 0; t < 256; t++){
		wB += histData[t];
		if (wB == 0){
			continue;
		}
		wF = aantalpixels - wB;
		if (wF == 0){
			break;
		}
		sumB += (float)(t * histData[t]);
		float mB = sumB / wB;
		float mF = (sum - sumB) / wF;

		float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

		if (varBetween > varMax){
			varMax = varBetween;
			threshold = t;
		}
	}

	return valueImage;
}