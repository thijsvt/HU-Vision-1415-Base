/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once
#include "PreProcessing.h"
#include "intensityImageStudent.h"
#include "intensityImage.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath> 

class StudentPreProcessing : public PreProcessing {
public:
	IntensityImage * stepToIntensityImage(const RGBImage &image) const;
	IntensityImage * stepScaleImage(const IntensityImage &image) const;
	IntensityImage * stepEdgeDetection(const IntensityImage &image) const;
	IntensityImage * stepThresholding(const IntensityImage &image) const;
private:
	RGBImage *RGBArray;
	const static int kernel5x5[5][5];
	const static int LapKernel5x5[5][5];

};