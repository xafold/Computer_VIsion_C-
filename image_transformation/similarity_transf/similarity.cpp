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
double scale_factor_a= 1.5;
double scale_a = 1/scale_factor_a;
double scale_factor_b= 1.5;
double scale_b = 1/scale_factor_b;
double tx = 50;
double ty= 60;
// Defining the transformation matrix;
double mydata[] = {scale_a, -scale_b, tx, scale_b, scale_a, ty};
Mat transformation(2, 3, CV_64F, mydata);

// Calculating the new dimensions of the transformed matrix
int newWidth = static_cast<int>(image.cols * (1.0 / scale_a));
int newHeight = static_cast<int>(image.rows * (1.0 / scale_a));

// Making sure that new dimensions are large enough to add translation as well
newWidth = std::max(newWidth, image.cols + static_cast<int>(abs(tx)));
newHeight = std::max(newHeight, image.rows + static_cast<int>(abs(ty)));

int midx = newWidth / 2;
int midy = newHeight / 2;

Mat transformed(newHeight, newWidth, image.type());

for (int y = 0; y < newWidth; y++) {
    for (int x = 0; x < newHeight; x++) {
        // Calculating the transformed coordinates
        double srcX = transformation.at<double>(0, 0) * (x-midx) + transformation.at<double>(0, 1) * (y-midy) + (image.cols / 2) + transformation.at<double>(0, 2);
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
