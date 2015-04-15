//
//  main.cpp
//  featureMatching
//
//  Created by Jeff Ithier on 22/03/2015.
//  Copyright (c) 2015 jeff. All rights reserved.
//

#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/gpu/gpu.hpp>

#include "functions.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    /* Initialise resources. */
    
    std::vector<KeyPoint> kp1, kp2;       // Vector of key points.
    cv::Mat des1, des2;
    
    
    Mat img1, img2;
    string img1Name, img2Name;
    
    img1Name = "IMGP9267";
    img2Name = "IMGP9268";

    /* Load images as greyscale. */
    
    img1 = imread("images/IMGP9267.jpg", CV_LOAD_IMAGE_GRAYSCALE); // Read in grayscale.
    img2 = imread("images/IMGP9268.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    
    /* Find keypoints for all images. */

    ORB orb = ORB(3000);
    
    orb.detect(img1, kp1);
    orb.detect(img1, kp2);
    
    /* Calculate ORB descriptors for all key points. */
    
    orb.compute(img1, kp1, des1);
    orb.compute(img2, kp2, des2);
    
    /* Match the key points. */
    
    BFMatcher matcher(NORM_HAMMING, true);
    
    vector<vector<DMatch>> matches;                 // k sets of matches, so [k][2] elements.
                                                    // [k][1] matches to [k][2].
    matcher.knnMatch(des1, des2, matches, 1);       // Find the TWO best matches.
    
    // Filter to matches that ar
    
    /* Print keypoints to file in SIFT format. */
    
    writeKeyPointsToFile(&kp1, img1Name);
    writeKeyPointsToFile(&kp2, img2Name);
    
    /* Draw and print keypoints to be displayed (only for debugging). */
    
    Mat imageMatches;
    
    drawMatches(img1, kp1, img2, kp2, matches, imageMatches);
    
    namedWindow("image");
    
    imshow("image", imageMatches);
    
    waitKey(0);
    
    return 0;
    
}
