#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int maxCorners = 1000;
int maxTrackbar = 100;

RNG rng(12345);

/// Function header
void TrackFeatures( Mat, std::vector<Point2f> & );

/**
 * @function main
 */
int main( int argc, char** argv )
{
    Mat img = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );

    std::vector<Point2f> keypoints;
    TrackFeatures(img, keypoints);

    for (size_t i = 0; i < keypoints.size(); i++)
    {
        printf("%f %f\n", keypoints[i].x, keypoints[i].y);
    }

    return 0;
}

/**
 * @function goodFeaturesToTrack_Demo.cpp
 * @brief Apply Shi-Tomasi corner detector
 */

void TrackFeatures(Mat img, vector<Point2f> &corners)
{
    std::vector<Point2f> p2corners;

    if( maxCorners < 1 ) { maxCorners = 1; }

    /// Parameters for Shi-Tomasi algorithm
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;

    /// Apply corner detection
    goodFeaturesToTrack( img,
               corners,
               maxCorners,
               qualityLevel,
               minDistance,
               Mat(),
               blockSize,
               useHarrisDetector,
               k );
}

inline float sqr(float a) {return a * a; }

float pd(Point2f a, Point2f b)
{
    return(sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)));
}