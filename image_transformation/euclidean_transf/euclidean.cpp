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

// Euclidean transformation parameters
double angle = 45.0; 
double tx = 30.0;      
double ty = 40.0;      

// Converting the angle to radians

double theta = angle * CV_PI / 180.0;
double cosTheta = cos(theta);
double sinTheta = sin(theta);

Mat transformed;

int heightImg = static_cast<int>(round(abs(image.rows * sinTheta) +
                                            abs(image.cols * cosTheta)));
int widthImg = static_cast<int>(round(abs(image.cols * cosTheta) +
                                            abs(image.rows * sinTheta)));

transformed = Mat(heightImg, widthImg, image.type(), Scalar(0, 0, 0));

int midx = widthImg / 2;
int midy = heightImg / 2;
// Applying the transformtaion
for (int y = 0; y < heightImg; y++) {
    for (int x = 0; x < widthImg; x++) {
        int srcX = static_cast<int>(cosTheta * (x - midx) -
                                    sinTheta * (y - midy) + (image.cols / 2) - tx);
        int srcY = static_cast<int>(sinTheta * (x - midx) +
                                    cosTheta * (y - midy) + (image.rows / 2) + ty);

        // Checking if the source coordinates are within image bounds
        if (srcX >= 0 && srcX < image.cols && srcY >= 0 && srcY < image.rows) {
            transformed.at<Vec3b>(y, x) = image.at<Vec3b>(srcY, srcX);
        }
    }
}

imshow("Original Image", image);
imshow("Transformed Image", transformed);
waitKey(0);
return 0;
}