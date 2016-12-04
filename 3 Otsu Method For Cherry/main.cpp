//
//  main.cpp
//  Otsu_Method_for_Cherry
//
//  Created by Ching_Shing on 16/10/14.
//  Copyright © 2016年 com.sjtu. All rights reserved.
//
#include <algorithm>
#include <iostream>
#include <fstream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;
using namespace std;

// Use greyscale image to produce histogram
void show_histogram(string const& name, Mat1b const& image,Mat3b &hist_image)
{
    // Set histogram bins count
    int bins = 256;
    int histSize[] = {bins};
    // Set ranges for histogram bins
    float lranges[] = {0, 256};
    const float* ranges[] = {lranges};
    // create matrix for histogram
    Mat hist;
    int channels[] = {0};
    
    // create matrix for histogram visualization
    int const hist_height = 256;
    hist_image = Mat3b::zeros(hist_height, bins);
    
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
    
    double max_val=0;
    minMaxLoc(hist, 0, &max_val);
    
    // visualize each bin
    for(int b = 0; b < bins; b++) {
        float const binVal = hist.at<float>(b);
        int   const height = cvRound(binVal*hist_height/max_val);
        line
        ( hist_image
         , Point(b, hist_height-height), Point(b, hist_height)
         , Scalar::all(255)
         );
    }
    imshow(name, hist_image);

}

// Implementation of OTSU algorithm
int otsu(Mat3b const& img)
{
    
    int hist_[256];
    std::fill_n(hist_, 256, 0);
    
    for (int i=0; i<img.rows; i++)
        for (int j=0;j<img.cols;j++) {
            int pixelval = img.at<uchar>(i,j);
            hist_[pixelval] += 1;
        }
    
    float sum=0.0;
    for(int i = 0; i < 256; ++i)
        sum += i*hist_[i];
    
    float wb=0.0,wf=0.0,sumb=0.0,max=0.0;
    int threshold1=0;
    
    for (int t = 0; t < 256; t++) {
        wb += hist_[t];
        if(wb==0)
            continue;
        
        wf= img.cols*img.rows-wb;
        if(wf==0)
            break;
        
        sumb += (float)(t*hist_[t]);
        
        float mb = sumb/wb;
        float mf = (sum-sumb)/wf;
        float between = (float)wb*(float)wf*(mb-mf)*(mb-mf);
        
        if (between > max)	{
            threshold1 = t;
            max = between;
        }
    }
    
    return threshold1;
}

int main ( int argc, char **argv )
{
    Mat img;
    img = imread("cherry.png");
    cvtColor(img,img,CV_RGB2GRAY);

    // Use Otsu's Method to produce threshold
    int threshold1 = otsu(img);
    
    // Produce the optimal threshold value
    ofstream resultfile;
    resultfile.open ("Threshold_value.txt");
    resultfile <<"Threshold value = "<<threshold1;
    resultfile.close();
    
    // Produce the thresholded image after Otsu's method
    Mat otsu;
    threshold(img,otsu,threshold1,255,CV_THRESH_BINARY);
    imshow("Otsu's Method",otsu);
    imwrite( "Otsu's_Method_Image.jpg", otsu );
    
    // Produce the filtered image without background
    Mat filter;
    threshold(img,filter,threshold1,255,CV_THRESH_TOZERO);
    imshow("Filter", filter);
    imwrite( "Filter_Image.jpg", filter );
    
    // Produce the histogram
    Mat3b hist_image;
    show_histogram("Histogram", img, hist_image);
    imwrite( "Histogram.jpg", hist_image );
    
    waitKey();
    
    return 0;
}
