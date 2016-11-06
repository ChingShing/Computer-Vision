/**
 * File: main.cpp
 * Project: Spatial_Domain_Filters
 * --------------------------------
 * Written by Ching Shing, SJTU's junior
 * --------------------------------
 * The file is to generate a spatial domain filter,which has 3 modes:
 * 1 - Gaussian Blur
 * 2 - Mean Blur
 * 3 - Median Blur
 * --------------------------------
 * Too much work and quit it. Turn to MatLab's embrace!
 */


#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;


static int grassBlurRadius = 0;
static int grassBlurSigma = 0;

static double dilation_elem = 0;
static double dilation_size = 0;
static int const radiusRange = 20;//
static int const sigmaRange = 20;//
int grassBlur_outputflag = 0;
int dilate_outputflag = 0;
Mat src, grassBlur_dst, meanBlur_dst, medianBlur_dst;

static void grassBlur( int, void* );
static void meanBlur( int, void* );
static void medianBlur( int, void* );
static void grassBlurEngine(Mat &img, Mat &dst, double &radius, double &sigma);
static void meanBlurEngine(Mat &img, Mat &dst, double &radius, double &sigma);
static void medianBlurEngine(Mat &img, Mat &dst, double &radius, double &sigma);

/*
 * Show the photo and let user choose radius and sigma
 */
int main( int argc, char** argv ){
    src = imread( argv[1]);
    cvtColor(src,src,CV_RGB2GRAY);
    
    if( argc != 2 || !src.data ){
        return -1;
    }
    
    // Create window
    namedWindow( "Gaussian Blur Demo", CV_WINDOW_AUTOSIZE );
    namedWindow( "Mean Blur Demo", CV_WINDOW_AUTOSIZE );
    cvMoveWindow( "Mean Blur Demo", src.cols, 0 );
    namedWindow( "Median Blur Demo", CV_WINDOW_AUTOSIZE );
    cvMoveWindow( "Median Blur Demo", src.cols * 2, 0 );
    
    
    // Create Gaussian Blur Trackbar
    createTrackbar( "Radius", "Gaussian Blur Demo",
                   &grassBlurRadius, 20,
                   grassBlur );
    createTrackbar( "Kernel size:\n 2n +1", "Gaussian Blur Demo",
                   &grassBlurSigma, 20,
                   grassBlur );
    createTrackbar( "Output Result", "Gaussian Blur Demo",
                   &grassBlur_outputflag, 1,
                   grassBlur );
    /*
    // Create dilation Trackbar
    createTrackbar( "SE:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
                   &dilation_elem, max_elem,
                   Dilation );
    
    createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo",
                   &dilation_size, max_kernel_size,
                   Dilation );
    
    createTrackbar( "Output Result", "Dilation Demo",
                   &dilate_outputflag, 1,
                   Dilation );
    */
    // Default start
    grassBlur( 0, 0 );
    meanBlur( 0, 0 );
    
    waitKey();
    return 0;
}

static void grassBlur( int, void* ){
    double gbRadius, gbSigma;
    if(grassBlurRadius != 0 && grassBlurSigma != 0){
        gbRadius = grassBlurRadius;
        gbSigma = grassBlurSigma;
    }
    
    grassBlurEngine( src, grassBlur_dst, gbRadius, gbSigma);
    imshow( "Gaussian Blur Demo", grassBlur_dst );
    
    if (grassBlur_outputflag == 1) {
        string filename = "/Users/ching_shing/Documents/0Junior/Vision/SE342 Computer Vision/5 Spatial Domain Filters/grassBlur.png";
        imwrite(filename, grassBlur_dst);
    }
}

static void grassBlurEngine(Mat &src, Mat &dst, double &radius, double &sigma){
    src.copyTo(dst);
    double hei = src.rows;
    double wid = src.cols;

    for (double y = 0; y < hei; ++y)
    {
        for (double x = 0; x < wid; ++x)
        {
            
        }
        
    }
    
    
    
    
    
    
    
}
