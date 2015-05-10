#ifndef _STUDENTHISTOGRAM_H
#define _STUDENTHISTOGRAM_H
#include <map>
//in samenwerking met Kjeld Perquin en Yorrick Lans.

class IntensityImage;

enum class HISTOGRAM_TYPE{
	HORIZONTAL,
	VERTICAL,
	FULL
};
class StudentHistogram{
public:
	explicit StudentHistogram(const IntensityImage& image, HISTOGRAM_TYPE type = HISTOGRAM_TYPE::FULL, int x = 0, int y = 0, int w = 0, int h = 0);
	unsigned char operator[](const int index);
private:
	std::map<unsigned char, int> frequencyTable;
};
#endif