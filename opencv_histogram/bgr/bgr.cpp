#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
Mat src, dst;

String imageName( "/run/media/xafold/Games and Software/Task/utsavp/opencv_histogram/image_source/sample_image.png" );

if (argc > 1)
{
    imageName = argv[1];
}

src = imread( imageName);

if( src.empty() )
{ return -1; }

vector<Mat> bgr_planes;
split( src, bgr_planes );

int histSize = 256;

float range[] = { 0, 256 } ;
const float* histRange = { range };

bool uniform = true; 
bool accumulate = false;

Mat b_hist, g_hist, r_hist;

calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

// Drawing the histograms for B, G and R
int hist_w = 512; int hist_h = 400;
int bin_w = cvRound( (double) hist_w/histSize );

Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

for( int i = 1; i < histSize; i++ )
{
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                    Scalar( 255, 0, 0), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                    Scalar( 0, 255, 0), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                    Scalar( 0, 0, 255), 2, 8, 0  );
}

putText(histImage, "Red (R)", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);
putText(histImage, "Green (G)", Point(10, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
putText(histImage, "Blue (B)", Point(10, 70), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);


cv::imwrite("histogram.png", histImage);

cv::Mat combinedImage, combinedImage1;
cv::hconcat(bgr_planes[0], bgr_planes[1], combinedImage);

cv::hconcat(combinedImage, bgr_planes[2], combinedImage1);
cv::imshow("Combined Images", combinedImage1);

cv::imwrite("Combined_image.png", combinedImage1);
cv::waitKey();
return 0;
}
