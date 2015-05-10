#include "StudentHistogram.h"
#include "IntensityImage.h"
// in samenwerking met Kjeld Perquin en Yorrick Lans.

StudentHistogram::StudentHistogram(const IntensityImage& image, HISTOGRAM_TYPE type, int x, int y, int w, int h){
	switch (type){
	case HISTOGRAM_TYPE::FULL:
		for (auto pixelPos = 0; pixelPos < image.getWidth() * image.getHeight(); ++pixelPos){
			auto intensity = image.getPixel(pixelPos);
			frequencyTable[intensity] += 1;
		}
		break;
	case HISTOGRAM_TYPE::HORIZONTAL:
		for (auto xPos = x; xPos < x + w; ++xPos){
			auto blackAmount = 0;
			for (auto yPos = y; yPos < y + h; ++yPos){
				if (image.getPixel(xPos, yPos) == 0){
					blackAmount++;
				}
			}
			frequencyTable[xPos] = blackAmount;
		}
		break;
	case HISTOGRAM_TYPE::VERTICAL:
		for (auto yPos = y; yPos < y + h; ++yPos){
			auto blackAmount = 0;
			for (auto xPos = x; xPos < x + w; ++xPos){
				if (image.getPixel(xPos, yPos) == 0){
					blackAmount++;
				}
			}
			frequencyTable[yPos] = blackAmount;
		}
		break;
	}
}

unsigned char StudentHistogram::operator[](const int index){
	return frequencyTable[index];
}