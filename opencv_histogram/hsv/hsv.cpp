#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
Mat src, hsv;

String imageName( "/run/media/xafold/Games and Software/Task/utsavp/opencv_histogram/image_source/sample_image.png" );

if (argc > 1)
{
    imageName = argv[1];
}

src = imread( imageName);
cvtColor(src, hsv, COLOR_BGR2HSV);

if( src.empty() )
{ return -1; }

vector<Mat> hsv_planes;
split( hsv, hsv_planes );

int histSize = 256;

float range[] = { 0, 256 } ;
const float* histRange = { range };

bool uniform = true; 
bool accumulate = false;

Mat h_hist, s_hist, v_hist;

// Calculating the histogram values for Three HSV channels
calcHist( &hsv_planes[0], 1, 0, Mat(), h_hist, 1, &histSize, &histRange, uniform, accumulate );
calcHist( &hsv_planes[1], 1, 0, Mat(), s_hist, 1, &histSize, &histRange, uniform, accumulate );
calcHist( &hsv_planes[2], 1, 0, Mat(), v_hist, 1, &histSize, &histRange, uniform, accumulate );

// Drawing the histograms for H, S and V
int hist_w = 512; int hist_h = 400;
int bin_w = cvRound( (double) hist_w/histSize );

Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

// Normalizing value of histogram 
normalize(h_hist, h_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(s_hist, s_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(v_hist, v_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

for( int i = 1; i < histSize; i++ )
{
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(h_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(h_hist.at<float>(i)) ),
                    Scalar( 255, 0, 0), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(s_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(s_hist.at<float>(i)) ),
                    Scalar( 0, 255, 0), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(v_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(v_hist.at<float>(i)) ),
                    Scalar( 0, 0, 255), 2, 8, 0  );

}
// Putting text in Histogram.
putText(histImage, "Hue (H)", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);
putText(histImage, "Saturation (S)", Point(10, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
putText(histImage, "Value (V)", Point(10, 70), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

Mat h_colormap;

// Applying the colormap to the Hue Channel only
applyColorMap(hsv_planes[0], h_colormap, COLORMAP_HSV);

cv::imwrite("histogram.png", histImage);

cv::Mat combinedImage, combinedImage1;
cv::hconcat(hsv_planes[0], hsv_planes[1], combinedImage);

cv::hconcat(combinedImage, hsv_planes[2], combinedImage1);
cv::imshow("Combined Images", combinedImage1);

cv::imwrite("Combined_image.png", combinedImage1);
cv::waitKey();
return 0;
}
