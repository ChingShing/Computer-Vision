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
#include <iostream>

typedef unsigned char uchar;

using namespace cv;
using namespace std;

void erode_new(Mat& src, Mat& dst, Mat kernel, Point anchor=Point(-1,-1))
//void erode_new(Mat src,Mat erosion_dst,Mat element )
{
    while(1)
    {
    src.copyTo(dst);
    int ker_size = kernel.rows;
    int ker_center = ker_size/2;
    //int src_rows = src.rows;
    //int src_cols = src.cols;
    bool zeroflag = false;

// Add black boundaries to src
    Mat mat=src;
    copyMakeBorder(mat, mat, ker_center,ker_center,ker_center,ker_center, 0 );
    /*if (!mat.empty()) {
        imshow( "mat Demo", mat );
    }*/
    
// Convert tmpmat to a 2D vector array
    for (int y = ker_center; y < mat.rows - ker_center; ++y)
    {
        //uchar* row_ptr = mat.ptr<uchar>(y);
        for (int x = ker_center; x < mat.cols - ker_center; ++x)
        {
            //int val = row_ptr[x];
            //cout<<val<<" ";
            
            // Shortcut: black should be black
           /* if(val == 0)
            {
                //dst.at<int>(x,y)=0;
                //dst.zeros(x, y, CV_8U);
                //(dst.row(y-ker_center).col(x-ker_center)) = Scalar_<uchar>(0);
                //cout<<(dst.row(y-ker_center).col(x-ker_center))<<" ";
                break;
            }*/
            
            zeroflag = false;
            
            for (int i = 0; i < ker_size; i++)
            {
                uchar* ker_ptr = kernel.ptr<uchar>(i);
                uchar* mat_ptr = mat.ptr<uchar>(y+i-ker_center);
                for (int j = 0; j < ker_size; j++)
                {
                    int kerval = ker_ptr[j];
                    int matval = mat_ptr[x+j-ker_center];
                    
                    if(matval == 0 && kerval == 1 )
                    {
                        //dst.at<int>(x-ker_center,y-ker_center)=0;
                        //dst.zeros(x-ker_center,y-ker_center, CV_8U);
                        (dst.row(y-ker_center).col(x-ker_center)) = Scalar_<uchar>(0);
                        zeroflag=true;

                        break;
                    }
                    
                }
                if (zeroflag) {
                    break;
                }

            }
            if (!zeroflag) {
                //dst.at<int>(x-ker_center,y-ker_center)=255;
                //dst.ones(x-ker_center,y-ker_center, CV_8U)*255;
                 //cout<<"white ";
                (dst.row(y-ker_center).col(x-ker_center)) = Scalar_<uchar>(255);
                 //cout<<(dst.row(y-ker_center).col(x-ker_center))<<" ";
            }
            //cout<<(dst.row(x-ker_center)).col(y-ker_center)<<" ";
        }
    }
/*
    if (!dst.empty()) {
        imshow( "dst Demo", dst );
    }*/
    
    //erode(src,dst,kernel);

    
    
/*
    uchar **array = new uchar*[tmpmat.rows];
    for (int i=0; i<tmpmat.rows; ++i)
        array[i] = new uchar[tmpmat.cols];
    
    for (int i=0; i<tmpmat.rows; ++i)
    {
        for (int j=0; j<tmpmat.cols; ++j)
        {
            if(tmpmat.at<uchar>(i,j)=='[255]')array[i][j] = '255';
            else array[i][j] = '0';
        }
    }
    
    
    for (int i=0; i<tmpmat.rows; ++i) {
        for (int j=0; j<tmpmat.cols; ++j) {
            cout<<tmpmat.type()<<" "<<endl;
        }
    }*/
    
    /*
    vector<float> vector_col(src.cols,0);
    vector< vector<float> > vector_2d(tmpmat.rows,vector_col);
    for (int i = 0; i < tmpmat.rows; ++i) {
            vector_col.insert(vector_col.begin(), &(tmpmat.at<float>(i,0)), &(tmpmat.at<float>(i,tmpmat.cols-1)));
            vector_2d[i].insert(vector_2d[i].begin(),vector_col[0],vector_col[tmpmat.cols-1]);
            vector_col.assign(256,0);
    }
    
    vector<float> ele_col(element.cols,0);
    vector< vector<float> > ele_2d(element.rows,ele_col);
    for (int i = 0; i < element.rows; ++i) {
        ele_col.insert(ele_col.begin(),&(element.at<float>(i,0)), &(element.at<float>(i,element.cols-1)));
        ele_2d[i].insert(ele_2d[i].begin(),vector_col[0],ele_col[element.cols-1]);
        ele_col.assign(element.rows,0);
    }
    
// Erode
    // Iterate every pixel in tmpmat
    bool bool_pixel = true;
    for (int i = 0; i < tmpmat.rows; i++) {
        for (int j = 0; j < tmpmat.cols; j++) {
            
            // Use "and" operator for minimum bool value
            bool_pixel = (vector_2d[i][j] && ele_2d[0][0]);
            
            // Shortcut for zero value
            if (!bool_pixel)
            {
                erosion_dst.at<float>(i,j)=0;
                break;
           }

        
            for (int k = 0; k < ele_2d.size(); k++) {
                for (int l = 0; l < ele_col.size(); l++) {
                    bool_pixel = bool_pixel && (vector_2d[i+k][j+l] && ele_2d[k][l]) ;
                    
                    // Shortcut for zero value
                    if (!bool_pixel) break;
                    }
                
                // Shortcut for zero value
                //if (!bool_pixel) break;
            }
            
        // Fill in the pixel in erosion_dst
        if (!bool_pixel) erosion_dst.at<float>(i,j)=0;
        else erosion_dst.at<float>(i,j)=255;
            
            
            
        cout << "erosion_dst:"<<(erosion_dst.row(0)).col(0)<<std::endl;
            
        }
    }*/
    
    
    
    
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
int outputflag = 0;

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
    
    createTrackbar( "Output(OFF/ON)", "Erosion Demo",
                   &outputflag, 1,
                   Erosion );
    
    // Create dilation Trackbar
    createTrackbar( "SE:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
                   &dilation_elem, max_elem,
                   Dilation );
    
    createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo",
                   &dilation_size, max_kernel_size,
                   Dilation );
    if (!src.empty()) {
        imshow( "src Demo", src );
    }
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
    //std::cout << "element:"<<std::endl<<element<<std::endl;
    
    // Erode operation
    //Mat k =
    erode_new( src, erosion_dst, element );
    
    //Vec3b graypixel = src.at<Vec3b>(0,0);
    
    //if ((src.row(0)).col(0)==) {
        //std::cout << "src:"<<(src.row(0)).col(0)<<std::endl;
    //}
    
    //std::cout << "src:"<<graypixel<<std::endl;
    
    //std::cout << "erosion_dst:"<<erosion_dst.at<int>(0, 0)<<std::endl;
    //std::cout << "element:"<<std::endl<<(src.row(0)).col(0) << (element.row(0)).col(0)<<std::endl;

    //erosion_dst=src;
    
    if (!erosion_dst.empty()) {
        imshow( "Erosion Demo", erosion_dst );
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
    dilate( src, dilation_dst, element );
    imshow( "Dilation Demo", dilation_dst );
}


