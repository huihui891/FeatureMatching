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
#include <opencv2/features2d/features2d.hpp>
#include <string>

namespace fs = ::boost::filesystem;
using namespace std;
using namespace cv;

void getAllJPG(fs::path& path, vector<fs::path>& files);
void writeKeyPointsToFile(vector<KeyPoint>* inputPoints, string imageName);

#endif /* defined(__featureMatching__functions__) */
