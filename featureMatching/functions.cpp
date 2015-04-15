//
//  functions.cpp
//  featureMatching
//
//  Created by Jeff Ithier on 3/04/2015.
//  Copyright (c) 2015 jeff. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "functions.h"


namespace fs = ::boost::filesystem;     // Shorthand for boost filesystem namespace.
using namespace std;
using namespace cv;

/* Read all jpgs in a given directory */

void getAllJPG(fs::path& path, vector<fs::path>& files){
    
    if (!fs::exists(path) || !fs::is_directory(path)){
        cout << "Path is not a valid directory.";
        return;
    }
    
    fs::recursive_directory_iterator it(path);  // Iterator for this directory.
    fs::recursive_directory_iterator endit;     // Indicating the end of directory.
    
    while (it != endit){
        if (fs::is_regular_file(*it) && it->path().extension() == ".jpg"){
            files.push_back(it->path().filename());
            ++it;
        }
    }
    
};

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
