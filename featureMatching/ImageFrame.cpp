//
//  ImageFrame.cpp
//  featureMatching
//
//  Created by Jeff Ithier on 15/04/2015.
//  Copyright (c) 2015 jeff. All rights reserved.
//

#include <boost/filesystem.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "ImageFrame.h"

namespace           fs = ::boost::filesystem;;
using namespace     std;
using namespace     cv;

ImageFrame::ImageFrame(fs::path imagePath){
    
    fileName = imagePath.filename().string();
    fileStem = imagePath.stem().string();
    
    imgGray = imread("inputFiles/images/"+fileName, CV_LOAD_IMAGE_GRAYSCALE);
    
    ORB orb = ORB(3000);                            // ORB class for keypoint finding and matching.
    
    orb.detect(imgGray, keypoints);                 // Get key points in image.
    orb.compute(imgGray, keypoints, descriptors);   // Get ORB descriptors.
    descriptors.convertTo(descriptors, CV_32F);     // Need to convert to 32-bit for FLANN.
    
}

string              ImageFrame::getFileName(){
    return fileName;
}

string              ImageFrame::getFileStem(){
    return fileStem;
}

Mat                 ImageFrame::getImgGray(){
    return imgGray;
}
Mat                 ImageFrame::getDescriptors(){
    return descriptors;
}
vector<KeyPoint>    ImageFrame::getKeyPoints(){
    return keypoints;
}