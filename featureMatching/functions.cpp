//
//  functions.cpp
//  featureMatching
//
//  Created by Jeff Ithier on 3/04/2015.
//  Copyright (c) 2015 jeff. All rights reserved.
//

#include <fstream>

#include "functions.h"

#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


/* Write keypoints to file in SIFT format. */
void writeKeyPointsToFile(vector<KeyPoint>* inputPoints, string imageName){
    
    ofstream outputFile;
    
    outputFile.open(imageName+".sift");
    
    long numKeyPoints = inputPoints->size();
    
    // Num keypoints followed by "128"
    outputFile << numKeyPoints << " 128" << endl;
    
    for (int i = 0; i < numKeyPoints; i++) {
        
        // Image coordinate followed by two zeros.
        outputFile << inputPoints->at(i).pt.x << " " << inputPoints->at(i).pt.y << " 0" << " 0" << endl;
        
        
        // Six rows of 20 zeros.
        for(int j = 0; j < 6; j++){
            
            for (int k = 0; k < 20; k++){
                outputFile << 0 << " ";
            }
            
            outputFile << endl;
            
        }
        
        // One row of 8 zeros/
        for (int j = 0; j < 8; j++){
            outputFile << 0 << " ";
        }
        
        outputFile << endl;
        
    }
    
    outputFile.close();
    
}