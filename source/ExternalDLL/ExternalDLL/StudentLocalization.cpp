#include "StudentLocalization.h"
#include "StudentHistogram.h"
// in samenwerking met Kjeld Perquin en Yorrick Lans.

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	int headTopX = features.getFeature(Feature::FEATURE_HEAD_TOP).getX();
	int headTopY = features.getFeature(Feature::FEATURE_HEAD_TOP).getY();
	int headLeftX = features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getX();
	int headLeftY = features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getY();
	int headRightX = features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getX();
	int headRightY = features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getY();

	auto imageWidth = image.getWidth();
	auto imageHeight = image.getHeight();

	auto headWidth = headRightX - headLeftX;
	int segmentWidth = headWidth / 4.0;
	int segmentX = headLeftX + headWidth / 2.0 - 0.5 * segmentWidth;
	auto segmentY = 70;

	std::vector<int> correctPoints;
	std::vector<int> points;

	StudentHistogram verticalStrip{ image, HISTOGRAM_TYPE::VERTICAL, segmentX, segmentY, segmentWidth, imageHeight - headTopY };
	StudentHistogram middleVerticalStrip{ image, HISTOGRAM_TYPE::VERTICAL, headTopX, segmentY, 1, imageHeight - headTopY };
	for (auto y = segmentY; y < imageHeight - 1; ++y){
		if ((verticalStrip[y] == 0 && verticalStrip[y + 1] > 0) || (verticalStrip[y] > 0 && verticalStrip[y + 1] == 0)){
			points.push_back(y);
			if (points.size() % 2 == 0){
				StudentHistogram horizontalStrip{ image, HISTOGRAM_TYPE::HORIZONTAL, headTopX, points[points.size() - 2], 1, points[points.size() - 1] - points[points.size() - 2] };
				if (horizontalStrip[headTopX] > 0){
					correctPoints.push_back(points[points.size() - 2]);
					correctPoints.push_back(points[points.size() - 1]);
					auto someY = y;
					while (1){
						if (middleVerticalStrip[someY] > 0 && middleVerticalStrip[someY - 1] == 0){
							correctPoints[correctPoints.size() - 2] = someY;
							break;
							}
						--someY;
						}
						std::cout << correctPoints[correctPoints.size() - 2] << ',' << correctPoints[correctPoints.size() - 1] << std::endl;
				}
			}
		}
	}
	for (auto &e : correctPoints){
		std::cout << e << std::endl;
	}
	Point2D<double> bottomNose{ static_cast<double>(headTopX), correctPoints[0] + ((correctPoints[1] - correctPoints[0]) / 2.0) }; // elke 2 punten bijelkaar is een piek. 
	Point2D<double> topMouth{ static_cast<double>(headTopX), correctPoints[2] + ((correctPoints[3] - correctPoints[2]) / 2.0) };
	Point2D<double> bottomMouth{ static_cast<double>(headTopX), correctPoints[4] + ((correctPoints[5] - correctPoints[4]) / 2.0) };
	Point2D<double> middleMouth{ static_cast<double>(headTopX), topMouth.getY() + ((bottomMouth.getY() - topMouth.getY()) / 2.0) };
	Point2D<double> chin{ static_cast<double>(headTopX), correctPoints[6] + ((correctPoints[7] - correctPoints[6]) / 2.0) };
	std::cout << bottomNose.getY() << std::endl;
	std::cout << topMouth.getY() << std::endl;
	std::cout << bottomMouth.getY() << std::endl;
	std::cout << middleMouth.getY() << std::endl;
	std::cout << chin.getY() << std::endl;
	Feature noseBottom{ Feature::FEATURE_NOSE_BOTTOM, bottomNose };
	Feature mouthTop{ Feature::FEATURE_MOUTH_TOP, topMouth };
	Feature mouthBottom{ Feature::FEATURE_MOUTH_BOTTOM, bottomMouth };
	Feature mouthMiddle{ Feature::FEATURE_MOUTH_CENTER, middleMouth };
	Feature chinCenter{ Feature::FEATURE_CHIN, chin };
	features.putFeature(noseBottom);
	features.putFeature(mouthTop);
	features.putFeature(mouthBottom);
	features.putFeature(mouthMiddle);
	features.putFeature(chinCenter);
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}