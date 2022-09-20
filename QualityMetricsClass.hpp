//
//  QualityMetricsClass.hpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 3/15/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#ifndef QualityMetricsClass_hpp
#define QualityMetricsClass_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double myPsnr(Mat originalImg, Mat compressedImg);
double mySnr(Mat src);
double myMse(Mat originalImg, Mat compressedImg);
double mySsim(Mat originalImg,Mat compressedImg);
void myEme(Mat src,int N);

#endif /* QualityMetricsClass_hpp */
