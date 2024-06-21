#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

struct LineParameters {
    float slope;
    float intercept;
};

Mat region_of_interest_smooth_lines(const Mat& image, const pair<Vec4i, Vec4i>& smooth_lines) {
    int height = image.rows;
    int width = image.cols;

    Vec4i left_line = smooth_lines.first;
    Vec4i right_line = smooth_lines.second;

    Mat mask = Mat::zeros(image.size(), image.type());

    // Creating a polygon for new the region of interest overlay
    vector<Point> roi_points;
    roi_points.push_back(Point(left_line[0], left_line[1]));
    roi_points.push_back(Point(left_line[2], left_line[3]));
    roi_points.push_back(Point(right_line[2], right_line[3]));
    roi_points.push_back(Point(right_line[0], right_line[1]));

    // New ROI with a green color
    fillPoly(mask, vector<vector<Point>>{roi_points}, Scalar(0, 255, 0));

    // Applying the weighted mask to original image
    Mat masked_image;
    addWeighted(image, 1.0, mask, 0.3, 0, masked_image);

    return masked_image;
}

// Displayign the Left and Right lane line
Mat displayLines(Mat& image, const pair<Vec4i, Vec4i>& lines) {
    Vec4i left_line = lines.first;
    Vec4i right_line = lines.second;
    Mat image1;
    image.copyTo(image1);

    // Displaying the left lane 
    line(image1, Point(left_line[0], left_line[1]), Point(left_line[2], left_line[3]), Scalar(255, 0, 0), 10);

    // Displaying the right line
    line(image1, Point(right_line[0], right_line[1]), Point(right_line[2], right_line[3]), Scalar(255, 0, 0), 10);

    return image1;
}

// Calculating the cordinates ([x1,y1],[x2,y2]) from given slope and intercept
Vec4i getLineCoordinatesFromParameters(const Mat& image, const LineParameters& lineParameters) {
    float slope = lineParameters.slope;
    float intercept = lineParameters.intercept;

    int y1 = image.rows; 
    int y2 = static_cast<int>(y1 * (3.2/ 5));
    int x1 = static_cast<int>((y1 - intercept) / slope);
    int x2 = static_cast<int>((y2 - intercept) / slope);

    return Vec4i(x1, y1, x2, y2);
}

// Calcultaing avearage slope and intercept from given array of slopes and intercepts
LineParameters calculate_average(const vector<LineParameters>& lines) {
    LineParameters average = {0.0f, 0.0f};

    for (const auto& line : lines) {
        average.slope += line.slope;
        average.intercept += line.intercept;
    }

    // Calculating the average of slope and intercept
    if (!lines.empty()) {
        average.slope /= lines.size();
        average.intercept /= lines.size();
    }

    return average;
}

// Calcultaing slopes and intercepts from the give points i.e ([x1,y1],[x2,y2])
LineParameters calc_slope_intercept(const Point& p1, const Point& p2) {
    Vec4f line;
    vector<Point2f> points = {static_cast<Point2f>(p1), static_cast<Point2f>(p2)};
    // Fitting the points obtained from the Hough lines
    fitLine(points, line, DIST_L2, 0, 0.01, 0.01);
    float slope = line[1] / line[0];
    float intercept = p1.y - slope * p1.x;
    return {slope, intercept};
}

// Smoothing out the lines obtained from Hough Lines
pair<Vec4i, Vec4i> get_smooth_lines(vector<Vec4i>lines, Mat &image){
    // Creating the array of vectors of left_fit and right_fit lines
    vector<LineParameters> left_fit;
    vector<LineParameters> right_fit;
    for (size_t i = 0; i < lines.size(); i++)
    {   
        // Calculating the slope and ontercept for two points i.e (x1,y1), (x2,y2)
        Point point1(lines[i][0], lines[i][1]);
        Point point2(lines[i][2], lines[i][3]);

        //Calculating the slope and intercept from the two points       
        LineParameters params = calc_slope_intercept(point1, point2);

        // Differentiating the left_line or right_line from the slope
        if (params.slope < 0) {
            left_fit.push_back(params);
        } else {
            right_fit.push_back(params);
        }

    }
    // Calculating average of slope and intercept of left and right fitted line 
    LineParameters left_fit_average = calculate_average(left_fit);
    LineParameters right_fit_average = calculate_average(right_fit);

    // Getting the line co-ordinate from the average fitted left and right lines
    Vec4i left_line = getLineCoordinatesFromParameters(image, left_fit_average);
    Vec4i right_line = getLineCoordinatesFromParameters(image, right_fit_average);

    return make_pair(left_line, right_line);
}

// Displaying the Hough Lines on the image
Mat display_hough_line(vector<Vec4i>lines, const Mat &image) 
{ 
    Mat image_with_lines = image.clone(); // Creating copy of the input image

    for (size_t i = 0; i < lines.size(); i++)
    {
        line(image_with_lines, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
    }

    return image_with_lines;
}

// Calculating the Houg Line
vector<Vec4i> hough_lines(const Mat &image) 
{ 
    Mat image_with_lines = image.clone();
    vector<Vec4i> lines;
    HoughLinesP(image, lines, 1, CV_PI/180, 80, 30, 10);
    return lines;
} 

// 
Mat region_of_interest(Mat &image){

    int height = image.rows;
    int width = image.cols;

    // Defining the triangular ROI
    vector<Point> triangle;
    triangle.push_back(Point(300, height));
    triangle.push_back(Point(width, height));
    triangle.push_back(Point(width - 500, static_cast<int>(height / 1.8)));

    Mat black_image = Mat::zeros(image.size(), image.type());

    // Creating a mask
    fillPoly(black_image, triangle, 255); 

    // Applying the mask to the original image
    Mat masked_image;
    bitwise_and(image, black_image, masked_image);

    return masked_image;
}

int main() {
    string videoFilePath = "/run/media/xafold/Games and Software/Task/utsavp/lane_detection/video/lane_detection_test.mp4";
    VideoCapture cap(videoFilePath);

    if(!cap.isOpened()){
        cout << "Error opening video stream " << endl;
        return -1;
    }
    // For Saving Output video
    int frames_per_second = 25;
    Size frame_size(1280, 720);
    VideoWriter video_writer2("/run/media/xafold/Games and Software/Task/utsavp/lane_detection/output/canny.avi", VideoWriter::fourcc('X', 'V', 'I', 'D'), frames_per_second, frame_size, false);

    while(1){
        Mat image, imgGrayscale, imgBlurred, imgCanny,roi_image, hough_image,output_image;

        cap >> image;

        if (image.empty()) {
            cout << "End of video stream" << endl;
            break;
        }

        cvtColor(image, imgGrayscale, COLOR_BGR2GRAY);
        GaussianBlur(imgGrayscale,imgBlurred,Size(5, 5),1.8);
        Canny(imgBlurred,imgCanny,50,150);

        roi_image = region_of_interest(imgCanny);

        vector<Vec4i> houghLines = hough_lines(roi_image);
        hough_image = display_hough_line(houghLines,image);
        pair<Vec4i, Vec4i> smooth_lines = get_smooth_lines(houghLines, image);
        output_image =  displayLines(image, smooth_lines);
        Mat green_roi_image = region_of_interest_smooth_lines(output_image, smooth_lines);

        imshow("Original_image", image);

        imshow("ROI_image", roi_image);
        imshow("Hough_image", hough_image);
        imshow("Smooth_line_image", output_image);
        imshow("Green_ROI", green_roi_image);

        video_writer2.write(imgCanny);

        char c=(char)waitKey(25);
        if(c==27)
        break;
    }
    video_writer2.release();

    cap.release();
    cv::destroyAllWindows();
    return 0;
}