#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;       

int main(int argc, char** argv) {
VideoCapture capWebcam(0);   // declaring a VideoCapture object to associate webcam, 0 means use default webcam

// First we declare the variables we are going to use
Mat grad;

Mat imageOriginal;        // input image
Mat imageGrayscale;       // grayscale image
Mat imageBlurred;         // blurred image
Mat imageSobel;

char charCheckForEscKey = 0;
int scale = 2;
int delta = 5;
int frame = 0;
const int save = 60; // Saving one sample output image every 60 frames

while (charCheckForEscKey != 27 && capWebcam.isOpened()) {   // Taking frames from webcam until the Esc key is pressed or webcam connection is lost
bool frameReadSuccessfully = capWebcam.read(imageOriginal);   // getting next frame

cvtColor(imageOriginal, imageGrayscale, COLOR_BGR2GRAY);                   

GaussianBlur(imageGrayscale, imageBlurred, Size(3, 3), 1.8);

// Sobel edge detection
Mat grad_x, grad_y;
Mat abs_grad_x, abs_grad_y;
Sobel(imageBlurred, grad_x, CV_16S, 1, 0, 3, scale, delta);
Sobel(imageBlurred, grad_y, CV_16S, 0, 1, 3, scale, delta);

// Converting gradient x & y back to CV_8U
convertScaleAbs(grad_x, abs_grad_x);
convertScaleAbs(grad_y, abs_grad_y);

addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, -1, imageSobel);

namedWindow("imgOriginal");      
namedWindow("imgSobel");

imshow("imgOriginal", imageOriginal);
imshow("imgSobel", imageSobel);


charCheckForEscKey = waitKey(1);
frame++;
if (frame == save) {
    imwrite("/run/media/xafold/Games and Software/Task/utsavp/edge_detection/sobel/output/output.png", imageSobel);
    frame = 0; 
}

}

return(0);
}