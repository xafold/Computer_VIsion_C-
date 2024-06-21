#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
Mat src = imread("/run/media/xafold/Games and Software/Task/utsavp/image_transformation/images/lena.png");

int dx = 60;  
int dy = 50;  

Mat dst(src.rows, src.cols, src.type());

for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++) {
        int new_i = i + dy;
        int new_j = j + dx;

        if (new_i >= 0 && new_i < src.rows && new_j >= 0 && new_j < src.cols) {
            dst.at<Vec3b>(new_i, new_j) = src.at<Vec3b>(i, j);
        }
    }
}

cv::Mat combinedImage;
cv::hconcat(src, dst, combinedImage);
cv::imwrite("combined_images.png", combinedImage);
cv::imshow("Translation", combinedImage);
cv::waitKey(0);
return 0;
}
