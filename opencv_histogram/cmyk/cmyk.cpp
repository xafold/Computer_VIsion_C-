#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void rgb2cmyk(cv::Mat& img, std::vector<cv::Mat>& cmyk) {
    // Allocate cmyk to store 4 componets
    for (int i = 0; i < 4; i++) {
        cmyk.push_back(cv::Mat(img.size(), CV_8UC1));
    }

    // Getting rgb
    std::vector<cv::Mat> rgb;
    cv::split(img, rgb);

    // rgb to cmyk conversion
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            float r = (int)rgb[2].at<uchar>(i, j) / 255.;
            float g = (int)rgb[1].at<uchar>(i, j) / 255.;
            float b = (int)rgb[0].at<uchar>(i, j) / 255.;
            float k = std::min(std::min(1- r, 1- g), 1- b);         

            cmyk[0].at<uchar>(i, j) = (1 - r - k) / (1 - k) * 255.;
            cmyk[1].at<uchar>(i, j) = (1 - g - k) / (1 - k) * 255.;
            cmyk[2].at<uchar>(i, j) = (1 - b - k) / (1 - k) * 255.;
            cmyk[3].at<uchar>(i, j) = k * 255.;
        }
    }
}

int main(int argc, char** argv) {
cv::Mat src = cv::imread("/run/media/xafold/Games and Software/Task/utsavp/opencv_histogram/image_source/sample_image.png");
std::vector<cv::Mat> dst;
rgb2cmyk(src, dst);

int histSize = 256;

float range[] = { 0, 256 } ;
const float* histRange = { range };

bool uniform = true; 
bool accumulate = false;

Mat c_hist, m_hist, y_hist, k_hist;

calcHist( &dst[0], 1, 0, Mat(), c_hist, 1, &histSize, &histRange, uniform, accumulate );
calcHist( &dst[1], 1, 0, Mat(), m_hist, 1, &histSize, &histRange, uniform, accumulate );
calcHist( &dst[2], 1, 0, Mat(), y_hist, 1, &histSize, &histRange, uniform, accumulate );
calcHist( &dst[3], 1, 0, Mat(), k_hist, 1, &histSize, &histRange, uniform, accumulate );

// Draw the histograms for C, M, Y and K.
int hist_w = 512; int hist_h = 400;
int bin_w = cvRound( (double) hist_w/histSize );

Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

normalize(c_hist, c_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(m_hist, m_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(y_hist, y_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(k_hist, k_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

for( int i = 1; i < histSize; i++ )
{
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(c_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(c_hist.at<float>(i)) ),
                    Scalar( 255, 0, 0), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(m_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(m_hist.at<float>(i)) ),
                    Scalar( 0, 255, 0), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(y_hist.at<float>(i-1)) ) ,
                    Point( bin_w*(i), hist_h - cvRound(y_hist.at<float>(i)) ),
                    Scalar( 0, 0, 255), 2, 8, 0  );
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(k_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(k_hist.at<float>(i)) ),
                Scalar( 255, 255, 255), 2, 8, 0  );
}
// Putting text in Histogram.
putText(histImage, "Cyan (C)", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);
putText(histImage, "Magenta (M)", Point(10, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
putText(histImage, "Yellow (Y)", Point(10, 70), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);
putText(histImage, "Key/Black (K)", Point(10, 90), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);


cv::imwrite("histogram.png", histImage);

cv::Mat combinedImage, combinedImage1, combinedImage2;
cv::hconcat(dst[0], dst[1], combinedImage);

cv::hconcat(combinedImage, dst[2], combinedImage1);
cv::hconcat(combinedImage1, dst[3], combinedImage2);
cv::imshow("Combined Images", combinedImage2);

cv::imwrite("Combined_image.png", combinedImage2);
cv::waitKey();
return 0;
}
