//
//  functions.h
//  featureMatching
//
//  Created by Jeff Ithier on 3/04/2015.
//  Copyright (c) 2015 jeff. All rights reserved.
//

#ifndef __featureMatching__functions__
#define __featureMatching__functions__

#include <stdio.h>
#include <vector>
#include <string>

#include <opencv2/features2d/features2d.hpp>

#include "ImageFrame.h"

namespace fs = ::boost::filesystem;
using namespace std;
using namespace cv;

void getAllJPG(fs::path& path, vector<fs::path>& files);
void writeKeyPointsToFile(vector<KeyPoint>* inputPoints, string imageName);
void writeMatchesToFile(vector<ImageFrame>* images, vector<DMatch>* matches, int idx1, int idx2);
void writeDescriptorsToFile(vector<ImageFrame>* images);

#endif /* defined(__featureMatching__functions__) */
