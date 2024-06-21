#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

int main() {
Mat image = imread("/run/media/xafold/Games and Software/Task/utsavp/image_transformation/images/lena.png");


double scale_factor= 0.7;
double scale = 1/scale_factor;
// Defining the transformation matrix;
double mydata1[] = {1, 0.2, 0, 0.2, 1, 0, 0, 0, 1}; // Shear matrix with 0.2 shear in x direction only
double mydata2[] = {scale, 0, 0, 0, scale, 1, 0, 0, 1}; // Scale matrix with 1 scaling on x and y direction
double mydata3[] = {1, 0, 0, 0, 1, 0, 0.0006, 0.0006, 1}; // Elation matrix in which v1=0.005 and v2=0.005 and v=1

Mat shear(3, 3, CV_64F, mydata1);
Mat scaling(3, 3, CV_64F, mydata2);
Mat elations(3, 3, CV_64F, mydata3);

Mat transformation = shear * scaling * elations ;


// Calculating the new dimensions of the transformed matrix
int newWidth = static_cast<int>(image.cols * 1.5);
int newHeight = static_cast<int>(image.rows * 1.5);

Mat transformed(newHeight, newWidth, image.type());

for (int y = 0; y < newWidth; y++) {
    for (int x = 0; x < newHeight; x++) {
        // Calculating the transformed coordinates
        double srcX = (transformation.at<double>(0, 0) * x + transformation.at<double>(0, 1) * y + transformation.at<double>(0, 2))/
        (transformation.at<double>(2, 0) * x + transformation.at<double>(2, 1) * y + transformation.at<double>(2, 2));
        double srcY = ( transformation.at<double>(1, 0) * x + transformation.at<double>(1, 1) * y + transformation.at<double>(1, 2))/
        (transformation.at<double>(2, 0) * x + transformation.at<double>(2, 1) * y + transformation.at<double>(2, 2));

        // Checking if the transformed coordinates are within the image bounds
        if (srcX >= 0 && srcX < image.cols && srcY >= 0 && srcY < image.rows) {
            transformed.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(static_cast<int>(srcY), static_cast<int>(srcX));
        }
    }
}
imshow("Original Image", image);
imshow("Transformed Image", transformed);
waitKey(0);
return 0;
}
