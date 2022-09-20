//
//  QualityMetricsClass.cpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 3/15/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#include "QualityMetricsClass.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;


int getMinFunc(int arr[], int n)
{
    int res = arr[0];
    for (int i = 1; i < n; i++)
        res = min(res, arr[i]);
    return res;
}

int getMaxFunc(int arr[], int n)
{
    int res = arr[0];
    for (int i = 1; i < n; i++)
        res = max(res, arr[i]);
    return res;
}


double myPsnr(Mat originalImg, Mat compressedImg)
{
    //higher the better
    double mse = 0;
    double div = 0;
    int width = originalImg.cols;
    int height = originalImg.rows;
    double psnr = 0;
    for (int v = 0; v < height; v++)
    {
        for (int u = 0; u < width; u++)
        {
            div = originalImg.at<uchar>(v, u) - compressedImg.at<uchar>(v, u);
            
            mse += div*div;
            
        }
    }
    mse = mse / (width*height);
    psnr = 10 * log10(255 * 255 / mse);
    //printf("%lf\n", mse);
    //printf("%lf\n", psnr);
    return psnr;
}

double mySnr(Mat src){
    
    
    //higher is better
    int imgRows,imgCols,sum,count,val;
    double mean,var,std;
    imgRows=src.size().height;
    imgCols=src.size().width;
    sum=0;
    count=0;
    
    
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            sum+=src.at<uchar>(i,j);
            count++;
        }
    }
    mean=sum/count;
    sum=0;
    count=0;
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            val=pow(src.at<uchar>(i,j)-mean,2);
            sum+=val;
            count++;
        }
    }
    var=sum/count;
    std=sqrt(var);
    
    return mean/std;
}

double myMse(Mat originalImg, Mat compressedImg){
    double mse = 0;
    double div = 0;
    int width = originalImg.cols;
    int height = originalImg.rows;
    for (int v = 0; v < height; v++)
    {
        for (int u = 0; u < width; u++)
        {
            div = originalImg.at<uchar>(v, u) - compressedImg.at<uchar>(v, u);
            
            mse += div*div;
            
        }
    }
    mse = mse / (width*height);
    return mse;
}

double mySsim(Mat originalImg,Mat compressedImg){
    
    //A value of +1 indicates that the 2 given images are very similar or the same while a value of -1 indicates the 2 given images are very different.
    
    double C1 = 6.5025, C2 = 58.5225;
    
    int imgRows,imgCols,sumX,sumY,sumXY;
    double meanX,meanY,varX,varY,varXY,stdX,stdY,stdXY,valX,valY,valXY,ssim;
    imgRows=originalImg.size().height;
    imgCols=originalImg.size().width;
    sumX=0;
    sumY=0;
    sumXY=0;
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            sumX+=originalImg.at<uchar>(i,j);
            sumY+=compressedImg.at<uchar>(i,j);
        }
    }
    meanX=sumX/(imgRows*imgCols);
    meanY=sumY/(imgRows*imgCols);
    
    sumX=0;
    sumY=0;
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            valX=pow((originalImg.at<uchar>(i,j))-meanX,2);
            valY=pow((compressedImg.at<uchar>(i,j)-meanY),2);
            valXY=abs((originalImg.at<uchar>(i,j)-meanX)*(compressedImg.at<uchar>(i,j)-meanY));
            sumX+=valX;
            sumY+=valY;
            sumXY+=valXY;
        }
    }
    varX=sumX/(imgRows*imgCols-1);
    varY=sumY/(imgRows*imgCols-1);
    varXY=sumXY/(imgRows*imgCols-1);

    
    ssim=((2*meanX*meanY+C1)*(2*varXY+C2))/(((meanX*meanX)+(meanY*meanY)+C1)*((varX)+(varY)+C2));
    
    return ssim;
    
}

void myEme(Mat source,int N){
    
    // source image
    cv::Mat img;
    double sum=0.0,eme=0.0;;
    int numOfBlocks=0;
    
    for (int r = 0; r < img.rows; r += N)
        for (int c = 0; c < img.cols; c += N)
        {
            
            int neighborValues[N*N];
            int index=0;
            for(int i=r;i<i+N;i++){
                for(int j=c;j<j+N;j++){
                    neighborValues[index]=img.at<uchar>(i,j);
                    index++;
                }
            }
            
            int min=getMinFunc(neighborValues, N*N);
            cout<<"min: "<<min;
            
            int max=getMaxFunc(neighborValues, N*N);
            cout<<"max: "<<max<<endl;;
            int val=(max/(min+0.01));
            cout<<"val: "<<val<<endl;
            sum+=val;
            cout<<"sum: "<<sum<<endl;
            numOfBlocks++;
            cout<<"num of blocks: "<<numOfBlocks<<endl;
            
            
      
        }
    
    

    eme=sum/numOfBlocks;
    cout<<"eme: "<<eme<<endl;
    //return eme;
}
