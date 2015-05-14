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
    
    BFMatcher bMatcher(NORM_HAMMING, true);
    
    vector<vector<DMatch>> goodMatches;
    int numPairs = 0;
    
    /* Match images then print the matches file with ONLY good matches. */
    
    cout << "Preparing match file." << endl;
    
    for (int i = 0; i < images.size()-1; i++){
        
        // Print % done
        printf("%f done.\n", (float)(i/(images.size()-1))*100);
        
        for (int j = (i + 1); j < images.size(); j++){

            vector<DMatch> matches;                         // Has initial match results
            
            // Only match if there are keypoints on both images.
            if(images[i].getKeyPoints().size() > 0 && images[j].getKeyPoints().size()> 0){
                
                bMatcher.match(images[i].getDescriptors(), images[j].getDescriptors(), matches);
                
                /* Filter out poor matches. */
                
                vector<DMatch> goodMatchesTemp;                 // Gets good matches for the current pair of images.
                
                for (int k=0; k<matches.size(); k++) {
                    
                    if (matches.at(k).distance < 35) {
                        
                        goodMatchesTemp.push_back(matches.at(k));
                        
                    }
                    
                }
                
                goodMatches.push_back(goodMatchesTemp);         // Saves to vector with matches between all pairs.
                
                //printf("Matched image %i & %i; %lu good matches.\n", i, j, goodMatches.at(numPairs).size());
                
                writeMatchesToFile(&images, &(goodMatches.at(numPairs)), i, j);
                
                numPairs++;                                     // Keep track of how many matches have been made.
                
            }
        }
    }

    cout << "Writing descriptors to file." << endl;

    /* Print out descriptors of all keypoints in each image - will be used to form database after SFM. */
    
    writeDescriptorsToFile(&images);
    
    cout << "Done!" << endl;
    
    cout << "Preparing to display first match:" << endl;
    
    /* Draw and print keypoints to be displayed (only for debugging). */
    
    Mat imageMatches;
    vector<DMatch> matches = goodMatches.at(0);
    
    drawMatches(images[0].getImgGray(), images[0].getKeyPoints(),
                images[1].getImgGray(), images[1].getKeyPoints(), matches, imageMatches);
    
    namedWindow("image");
    
    imshow("image", imageMatches);
    
    waitKey(0);
    
    return 0;
    
}
