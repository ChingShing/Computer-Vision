//
//  main.cpp
//  SIFT
//
//  Created by Ching_Shing on 16/12/4.
//  Copyright © 2016年 com.sjtu. All rights reserved.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(){
    
    //Sift 方法
    //读取图像
    Mat input1=imread("/Users/ching_shing/Documents/0Junior/Vision/SE342 Computer Vision/8 SIFT/SIFT/image.jpg",1);
    Mat input2=imread("/Users/ching_shing/Documents/0Junior/Vision/SE342 Computer Vision/8 SIFT/SIFT/image_p.jpg",1);
    Mat output1, output2;
    
    SiftFeatureDetector sift_detector;
    vector<KeyPoint> keypoint1,keypoint2;
  
    //第一张图的描述点
    sift_detector.detect(input1,keypoint1);
    drawKeypoints(input1,keypoint1,output1);
    
    //第二张图的描述点
    sift_detector.detect(input2,keypoint2);
    drawKeypoints(input2,keypoint2,output2);
    
    SiftDescriptorExtractor extractor;
    Mat descriptor1,descriptor2;
    //计算特征向量
    extractor.compute(input1,keypoint1,descriptor1);
    extractor.compute(input2,keypoint2,descriptor2);
    
    BruteForceMatcher<L2<float>> matcher;
    vector<DMatch> matches;
    Mat img_matches;
    
    //匹配特征向量
    matcher.match(descriptor1,descriptor2,matches);
    nth_element(matches.begin(), matches.begin()+30,matches.end());
    matches.erase(matches.begin() + 30, matches.end());
    //画出连线
    drawMatches(input1,keypoint1,input2,keypoint2,matches,img_matches);
    imshow("sift",img_matches);
    imwrite("sift.jpg",img_matches);
    
    
     //Surf方法:
    
     Mat input1_surf=imread("/Users/ching_shing/Documents/0Junior/Vision/SE342 Computer Vision/8 SIFT/SIFT/image.jpg",1);
     Mat input2_surf=imread("/Users/ching_shing/Documents/0Junior/Vision/SE342 Computer Vision/8 SIFT/SIFT/image_p.jpg",1);
     Mat output1_surf, output2_surf;
     SurfFeatureDetector surf_detector;
     surf_detector.detect(input1_surf,keypoint1);
    
     //第一张图的描述点
     sift_detector.detect(input1_surf,keypoint1);
     drawKeypoints(input1_surf,keypoint1,output1_surf);
     //第二张图的描述点
     sift_detector.detect(input2_surf,keypoint2);
     drawKeypoints(input2_surf,keypoint2,output2_surf);
     
     SurfDescriptorExtractor extractor_surf;
     Mat descriptor1_surf,descriptor2_surf;
     Mat img_matches_surf;
    
     BruteForceMatcher<L2<float>> matcher_surf;
     vector<DMatch> matches_surf;
    
     //计算特征向量
     extractor_surf.compute(input1_surf,keypoint1,descriptor1_surf);
     extractor_surf.compute(input2_surf,keypoint2,descriptor2_surf);
     //匹配特征向量
     matcher_surf.match(descriptor1_surf,descriptor2_surf,matches_surf);
     nth_element(matches_surf.begin(), matches_surf.begin()+30,matches_surf.end());
     matches_surf.erase(matches_surf.begin() + 30, matches_surf.end());
     //画出连线
     drawMatches(input1_surf,keypoint1,input2_surf,keypoint2,matches_surf,img_matches_surf);
     imshow("surf",img_matches_surf);
     imwrite("surf.jpg",img_matches_surf);
    
     waitKey();
    
    
}
