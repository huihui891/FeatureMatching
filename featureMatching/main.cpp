//
//  main.cpp
//  featureMatching
//
//  Created by Jeff Ithier on 22/03/2015.
//  Copyright (c) 2015 jeff. All rights reserved.
//

#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/flann/flann.hpp>

#include "functions.h"

#include "ImageFrame.h"

namespace fs = ::boost::filesystem;
using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
   
    /* Read all files in the images directory. */
    
    vector<fs::path> files;                 // Vector containing path to all images to be matched.
    vector<ImageFrame> images;              // Class containing all images with their descriptors and keypoints.
    
    fs::path imageFolder ("images/");
    
    getAllJPG(imageFolder, files);
    
    cout << "Number of Images: " << files.size() << endl;
    
    /* Build the image structures. */
    
    for (int i = 0; i < files.size(); i++) {
        
        ImageFrame im(files[i]);
        images.push_back(im);
    }
    
    cout << "Images are now prepared for matching" << endl;

    /* Match the key points. */
    
    FlannBasedMatcher flannMatcher;
    
    vector<DMatch> matches;
    
    flannMatcher.match(images[0].getDescriptor(), images[1].getDescriptor(), matches);

    /* Print keypoints to file in SIFT format. */
    
    vector<KeyPoint> kp1 = images[0].getKeyPoints();
    vector<KeyPoint> kp2 = images[1].getKeyPoints();
    
    writeKeyPointsToFile(&kp1, images[0].getFileStem());
    writeKeyPointsToFile(&kp2, images[1].getFileStem());
    
    /* Draw and print keypoints to be displayed (only for debugging). */
    
    Mat imageMatches;
    
    drawMatches(images[0].getImgGray(), images[0].getKeyPoints(),
                images[1].getImgGray(), images[1].getKeyPoints(), matches, imageMatches);
    
    namedWindow("image");
    
    imshow("image", imageMatches);
    
    waitKey(0);
    
    return 0;
    
}
