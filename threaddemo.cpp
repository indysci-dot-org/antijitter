#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int maxCorners = 1000;
int maxTrackbar = 100;

RNG rng(12345);

/**
 * @function main
 */
int main( int argc, char** argv )
{
    int x, y;

    Mat img = imread( argv[1], 1 );

    std::vector<Point2f> points;

    int i = 0;
    while (i < 200)
    {
      if (scanf("%i\t%i\n", &x, &y) == EOF)
        break;
      points.push_back(Point2f((float)x,(float)y));
      i++;
    }

    printf("points: %i\n", points.size());

    for( int i = 0; i < points.size(); i++ )
    { circle( img, points[i], 5, Scalar(rng.uniform(0,255), rng.uniform(0,255),
              rng.uniform(0,255)), -1, 8, 0 ); }

    /// Show what you got
    namedWindow( "res", CV_WINDOW_AUTOSIZE );
    imshow( "res", img );
    waitKey(0);

    return 0;
}