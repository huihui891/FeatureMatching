//
//  ImageFrame.h
//  featureMatching
//
//  Created by Jeff Ithier on 15/04/2015.
//  Copyright (c) 2015 jeff. All rights reserved.
//

#ifndef __featureMatching__ImageFrame__
#define __featureMatching__ImageFrame__

#include <string>
#include <stdio.h>

#include <boost/filesystem.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

namespace fs = ::boost::filesystem;
using namespace std;
using namespace cv;


class ImageFrame{

private:
    
    string fileName;
    string fileStem;
    
    Mat imgGray;
    
    vector<KeyPoint> keypoints;
    Mat descriptors;
    
public:
    
    ImageFrame(fs::path imagePath);
    
    string              getFileName();
    string              getFileStem();
    Mat                 getImgGray();
    Mat                 getDescriptor();
    vector<KeyPoint>    getKeyPoints();
    
};


#endif /* defined(__featureMatching__ImageFrame__) */
