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
    
    fs::path imageFolder ("inputFiles/images/");
    
    getAllJPG(imageFolder, files);
    
    cout << "Number of Images: " << files.size() << endl;
    cout << "Detecting keypoints & generating descriptors." << endl;
    
    /* Build the image structures. */
    
    for (int i = 0; i < files.size(); i++) {
        
        ImageFrame im(files[i]);
        images.push_back(im);
    }

    cout << "Matching all images." << endl;

    /* Print keypoints to file in SIFT format. */
    
    for(int i = 0; i < images.size(); i++){
        vector<KeyPoint> kp = images[i].getKeyPoints();
        writeKeyPointsToFile(&kp, images[i].getFileStem());
    }
    
    /* Match the key points. */
    
    FlannBasedMatcher flannMatcher;
    
    vector<DMatch> matches;

    flannMatcher.match(images[0].getDescriptor(), images[1].getDescriptor(), matches);
    
    /* Print the matches file. */
    
    cout << "Preparing match file." << endl;
    
    for (int i = 0; i < images.size(); i++){
        for (int j = (i + 1); j < images.size(); j++){
            
            vector<DMatch> matches;
            flannMatcher.match(images[i].getDescriptor(), images[j].getDescriptor(), matches);
            
            writeMatchesToFile(&images, &matches, i, j);
            
        }
    }

    cout << "Done!" << endl;
    
//    /* Draw and print keypoints to be displayed (only for debugging). */
//    
//    Mat imageMatches;
//    
//    drawMatches(images[0].getImgGray(), images[0].getKeyPoints(),
//                images[1].getImgGray(), images[1].getKeyPoints(), matches, imageMatches);
//    
//    namedWindow("image");
//    
//    imshow("image", imageMatches);
//    
//    waitKey(0);
    
    return 0;
    
}
