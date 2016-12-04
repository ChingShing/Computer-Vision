//
//  main.cpp
//  Fundamental_Morphological_Operations
//
//  Created by Ching_Shing on 16/10/21.
//  Copyright © 2016年 com.sjtu. All rights reserved.
//

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned char uchar;

using namespace cv;
using namespace std;

void erode_new(Mat& src, Mat& dst, Mat kernel)
{
    while(1)
    {
    src.copyTo(dst);
    int ker_size = kernel.rows;
    int ker_center = ker_size/2;
    bool zeroflag = false;

    // Add black boundaries to src
    Mat mat;
    src.copyTo(mat);
    copyMakeBorder(mat, mat, ker_center,ker_center,ker_center,ker_center, 0 );
    
        // Erosion implemetation
        for (int y = ker_center; y < mat.rows - ker_center; ++y)
        {
            for (int x = ker_center; x < mat.cols - ker_center; ++x)
            {
                zeroflag = false;
            
                for (int i = 0; i < ker_size; i++)
                {
                    uchar* ker_ptr = kernel.ptr<uchar>(i);
                    uchar* mat_ptr = mat.ptr<uchar>(y+i-ker_center);
                    for (int j = 0; j < ker_size; j++)
                    {
                        int kerval = ker_ptr[j];
                        int matval = mat_ptr[x+j-ker_center];
                    
                        // Set dst pixel to black if minimun is found, breaks for next dst pixel
                        if(matval == 0 && kerval == 1 )
                        {
                            (dst.row(y-ker_center).col(x-ker_center)) = Scalar_<uchar>(0);
                            zeroflag=true;
                            break;
                        }
                    
                    }
                    if (zeroflag) {
                        break;
                    }

                }
                // Set dst pixel to white if minimun is not found
                if (!zeroflag) {
                    (dst.row(y-ker_center).col(x-ker_center)) = Scalar_<uchar>(255);
                }
            }
        }
    // Done to show
    return;
    }
}

void dilate_new(Mat& src, Mat& dst, Mat kernel)
{
    while(1)
    {
        src.copyTo(dst);
        int ker_size = kernel.rows;
        int ker_center = ker_size/2;
        bool zeroflag = false;
        
        // Add black boundaries to src
        Mat mat=src;
        copyMakeBorder(mat, mat, ker_center,ker_center,ker_center,ker_center, 0 );
        
        // Dilation implemetation
        for (int y = ker_center; y < mat.rows - ker_center; ++y)
        {
            for (int x = ker_center; x < mat.cols - ker_center; ++x)
            {
                zeroflag = false;
                
                for (int i = 0; i < ker_size; i++)
                {
                    uchar* ker_ptr = kernel.ptr<uchar>(i);
                    uchar* mat_ptr = mat.ptr<uchar>(y+i-ker_center);
                    for (int j = 0; j < ker_size; j++)
                    {
                        int kerval = ker_ptr[j];
                        int matval = mat_ptr[x+j-ker_center];
                        
                        // Set dst pixel to white if maximum is found, breaks for next dst pixel
                        if(matval == 255 && kerval == 1 )
                        {
                            (dst.row(y-ker_center).col(x-ker_center)) = Scalar_<uchar>(255);
                            zeroflag=true;
                            break;
                        }
                        
                    }
                    if (zeroflag) {
                        break;
                    }
                    
                }
                // Set dst pixel to black if minimun is not found
                if (!zeroflag) {
                    (dst.row(y-ker_center).col(x-ker_center)) = Scalar_<uchar>(0);
                }
            }
        }
        // Done to show
        return;
    }
}



// 全局变量
Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;
int erode_outputflag = 0;
int dilate_outputflag = 0;

/* Function Headers */
void Erosion( int, void* );
void Dilation( int, void* );

/* @function main */
int main( int argc, char** argv )
{
    // Load lena-binary.bmp
    src = imread( argv[1] );
    cvtColor(src,src,CV_RGB2GRAY);

    if( !src.data )
    { return -1; }
    
    // Create window
    namedWindow( "Erosion Demo", CV_WINDOW_AUTOSIZE );
    namedWindow( "Dilation Demo", CV_WINDOW_AUTOSIZE );
    cvMoveWindow( "Dilation Demo", src.cols, 0 );
    
    // Create erosion Trackbar

    createTrackbar( "SE:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
                   &erosion_elem, max_elem,
                   Erosion );

    createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",
                   &erosion_size, max_kernel_size,
                   Erosion );
    
    createTrackbar( "Output Result", "Erosion Demo",
                   &erode_outputflag, 1,
                   Erosion );
    
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

    // Default start
    Erosion( 0, 0 );
    Dilation( 0, 0 );
    
    waitKey();
    return 0;
}

/**  @function Erosion  */
void Erosion( int, void* )
{
    // user-defined erosion kernel
    int erosion_kernel;
    if( erosion_elem == 0 ){ erosion_kernel = MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_kernel = MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_kernel = MORPH_ELLIPSE; }
    
    Mat element = getStructuringElement( erosion_kernel,
                                        Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                        Point( erosion_size, erosion_size ) );
    // Erosion operation
    erode_new( src, erosion_dst, element );
    imshow( "Erosion Demo", erosion_dst );
    
    if (erode_outputflag == 1) {
        string filename = "/Users/ching_shing/Documents/大三上/Vision/Assignment/Assin2/Fundamental_Morphological_Operations/Fundamental_Morphological_Operations/erosion.bmp";
        imwrite(filename, erosion_dst);
    }
}

/* @function Dilation */
void Dilation( int, void* )
{
    // user-defined dilation kernel
    int dilation_kernel;
    if( dilation_elem == 0 ){ dilation_kernel = MORPH_RECT; }
    else if( dilation_elem == 1 ){ dilation_kernel = MORPH_CROSS; }
    else if( dilation_elem == 2) { dilation_kernel = MORPH_ELLIPSE; }
    
    Mat element = getStructuringElement( dilation_kernel,
                                        Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                        Point( dilation_size, dilation_size ) );
    // Dilate operation
    dilate_new( src, dilation_dst, element );
    imshow( "Dilation Demo", dilation_dst );
    
    if (dilate_outputflag == 1) {
        string filename = "/Users/ching_shing/Documents/大三上/Vision/Assignment/Assin2/Fundamental_Morphological_Operations/Fundamental_Morphological_Operations/dilation.bmp";
        imwrite(filename, dilation_dst);
    }
}


