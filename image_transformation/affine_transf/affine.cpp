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
double scale_factor= 1.2;
double scale = 1/scale_factor;
double tx = 50;
double ty = 40;

// Defining the transformation matrix;
double mydata[] = {scale, 0.2, tx, 0.2, scale, ty};
Mat transformation(2, 3, CV_64F, mydata);

// Calculating the new height and width of transformed matrix for scaling
int newWidth = static_cast<int>(image.cols * (1.0/scale) + 300);
int newHeight = static_cast<int>(image.rows * (1.0/scale)+ 300);

int midx = newWidth / 2;
int midy = newHeight / 2;

Mat transformed( newHeight,  newWidth, image.type());

for (int y = 0; y < newWidth; y++) {
    for (int x = 0; x < newHeight; x++) {
        // Calculating the transformed coordinates
        double srcX = transformation.at<double>(0, 0) * (x-midx) + transformation.at<double>(0, 1) * (y-midy)+ (image.cols / 2) - transformation.at<double>(0, 2);
        double srcY = transformation.at<double>(1, 0) * (x-midx) + transformation.at<double>(1, 1) * (y-midy) + (image.rows / 2) + transformation.at<double>(1, 2);

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
