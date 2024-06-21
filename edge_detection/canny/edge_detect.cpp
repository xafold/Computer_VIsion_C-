#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;       

int main() {
VideoCapture capWebcam(0);   // declaring a VideoCapture object to associate webcam, 0 means use default webcam


Mat imgOriginal;        // input image
Mat imgGrayscale;       // grayscale image
Mat imgBlurred;         // blurred image
Mat imgCanny;           // Canny edge image

char charCheckForEscKey = 0;
int lowTh = 30;
int highTh = 90;

int frame = 0;
const int save = 60; // Saving one sample output image every 60 frames

while (charCheckForEscKey != 27 && capWebcam.isOpened()) {   // Taking frames from webcam until the Esc key is pressed or webcam connection is lost
bool frameReadSuccessfully = capWebcam.read(imgOriginal);   // getting next frame

cvtColor(imgOriginal, imgGrayscale, COLOR_BGR2GRAY);                   

GaussianBlur(imgGrayscale,imgBlurred,Size(5, 5),1.8);

Canny(imgBlurred,imgCanny,lowTh,highTh);

namedWindow("imgOriginal");      
namedWindow("imgCanny");

// showing windows
imshow("imgOriginal", imgOriginal);                 
imshow("imgCanny", imgCanny);                       

charCheckForEscKey = cv::waitKey(1);

frame++;
if (frame == save) {
    imwrite("/run/media/xafold/Games and Software/Task/utsavp/edge_detection/canny/output/output.png", imgCanny);
    frame = 0; 
}

}

return(0);
}